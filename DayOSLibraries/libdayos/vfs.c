#include <vfs.h>
#include <service.h>
#include <message.h>
#include <string.h>
#include <sleep.h>
#include <driver.h>

int vfs_create_device(const char* path, unsigned int mode, unsigned int type)
{
	pid_t pid = get_service_pid("vfs");
	if(pid == 0)
		return SIGNAL_FAIL;
	
	message_t msg;
	msg.signal = VFS_SIGNAL_CREATE_DEVICE;

	struct vfs_request* request = (struct vfs_request*) &msg.message;
	
	request->magic = VFS_MAGIC;
	strcpy(request->path, path);
	request->mode = mode;
	request->param = type;
	
	send_message(&msg, pid);
	while(receive_message(&msg, pid) != MESSAGE_RECEIVED) sleep(1);
	return msg.signal;
}

int vfs_mount_device(const char* src, const char* dest, const char* fsd, unsigned int mode)
{
	pid_t pid = get_service_pid("vfs");
	pid_t fsd_pid = get_service_pid(fsd);
	
	if(pid == 0 || fsd_pid)
		return SIGNAL_FAIL;
	
	message_t msg;
	msg.signal = VFS_SIGNAL_MOUNT_DEVICE;
	
	struct vfs_request* request = (struct vfs_request*) &msg.message;
	
	request->magic = VFS_MAGIC;
	
	strcpy(request->path, src);
	request->mode = mode;
	send_message(&msg, pid);
	
	strcpy(request->path, src);
	request->param = fsd_pid;
	strcpy(msg.message, dest);
	send_message(&msg, pid);
	
	while(receive_message(&msg, pid) != MESSAGE_RECEIVED) sleep(1);
	return msg.signal;
}

int vfs_mount_ramdisk(const char* dest, unsigned int mode)
{
	pid_t pid = get_service_pid("vfs");
	if(pid == 0)
		return SIGNAL_FAIL;
	
	message_t msg;
	msg.signal = VFS_SIGNAL_MOUNT_RAMDISK;
	
	struct vfs_request* request = (struct vfs_request*) &msg.message;
	
	request->magic = VFS_MAGIC;
	strcpy(request->path, dest);
	request->mode = mode;
	send_message(&msg, pid);
	
	while(receive_message(&msg, pid) != MESSAGE_RECEIVED) sleep(1);
	return msg.signal;
}

#include <stdio.h>
int vfs_stat(struct vfs_file* file, struct stat* stat)
{
	if(!file || !stat) return -1;
	
	message_t msg;
	struct vfs_request* rq = (struct vfs_request*) &msg.message;
	
	msg.signal = FS_SIGNAL_STAT;
	strcpy(rq->path, file->path);
	
	send_message(&msg, file->device);
	while(receive_message(&msg, file->device) != MESSAGE_RECEIVED) sleep(1);
	
	if(msg.signal != SIGNAL_OK)
	{
		return -1;
	}
	
	struct stat* fs_stat = (struct stat*) &msg.message;
	*stat = *fs_stat;
	
	return 0;
}

#include <dayos.h>
int vfs_readdir(struct vfs_file* dir, struct vfs_file* dest, int num)
{
	if(!dir || !dest)
		return -1;
	
	message_t msg;
	struct vfs_request* rq = (struct vfs_request*) &msg.message;
	msg.signal = VFS_SIGNAL_READ_DIR;
	
	rq->param = num;
	strcpy(rq->path, dir->path);
	
	send_message(&msg, dir->device);
	while(receive_message(&msg, dir->device) != MESSAGE_RECEIVED) sleep(1);
	
	if(msg.signal != SIGNAL_OK)
	{
		return -1;
	}
	
	struct vfs_file* f = (struct vfs_file*) &msg.message;
	*dest = *f;
}