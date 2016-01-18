#include <dirent.h>
#include <message.h>
#include <stdlib.h>
#include <dayos.h>
#include <errno.h>
#include <string.h>
#include <driver.h>

int closedir(DIR* dir)
{
	free(dir);
}

DIR* opendir(const char* path)
{
	if (!path)
		return NULL;

	message_t msg;
	struct vfs_request* request = (struct vfs_request*)msg.message;
	struct vfs_file* vfile = (struct vfs_file*)msg.message;

	pid_t pid = get_service_pid("vfs");

	if (pid == 0)
	{
		errno = ENOENT;
		return NULL;
	}
	
	DIR* dir = malloc(sizeof(DIR));
	if (!dir)
	{
		errno = ENOMEM;
		return NULL;
	}
	
	request->magic = VFS_MAGIC;

	// FIXME: STRNCPY!
	strcpy(request->path, path);

	msg.signal = VFS_SIGNAL_OPEN_DIR;
	send_message(&msg, pid);
	if (receive_message_timeout(&msg, pid, 100, 5) == MESSAGE_ERR_RECEIVE)
	{
		free(dir);
		errno = ENOENT;
		return NULL;
	}

	if (msg.signal == SIGNAL_FAIL)
	{
		free(dir);
		errno = ENOENT;
		return NULL;
	}

	strcpy(dir->d_name, path);

	// Tell the FS driver (in case of a mounted device)
	if (vfile->type == VFS_MOUNTPOINT)
	{
		message_t mountmsg;
		struct vfs_file* fs_file = (struct vfs_file*) &mountmsg.message;
		struct vfs_request* fs_req = (struct vfs_request*) &mountmsg.message;
		mountmsg.signal = FS_SIGNAL_OPEN_DIR;
		strcpy(fs_req->path, vfile->path);

		send_message(&mountmsg, vfile->device);

		if (receive_message_timeout(&mountmsg, vfile->device, 100, 5) ==
				MESSAGE_ERR_RECEIVE ||
				mountmsg.signal != SIGNAL_OK)
		{
			errno = ENOENT;
			free(dir);
			return NULL;
		}
	
		dir->current.d_ino = fs_file->offset;
		
		dir->file = *fs_file;
		dir->file.device = vfile->device;
		dir->d_ino = mountmsg.size;
		return dir;
		//vfs_stat(vfile, &f->stat);
	}

	dir->d_ino = msg.size;
	dir->current.d_ino = vfile->offset;
	dir->file = *vfile;
	
	return dir;
}

struct dirent* readdir(DIR* dir)
{
	if(!dir) return NULL;
	
	struct vfs_file file;
	if(vfs_readdir(&dir->file, &file, dir->current.d_ino) == -1)
		return NULL;
	
	strcpy(dir->current.d_name, file.path);
	dir->current.d_ino = file.nid + 1; // Always point to the next entry.
	
	return &dir->current;
}

long telldir(DIR* dir)
{
	return dir->current.d_ino;
}

void seekdir(DIR* dir, long off)
{
	dir->current.d_ino = off;
}

void rewinddir(DIR* dir)
{
	dir->current.d_ino = dir->file.offset;
}