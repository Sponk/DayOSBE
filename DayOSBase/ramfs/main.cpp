#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dayos.h>
#include <driver.h>
#include <assert.h>
#include "Drive.h"

using namespace std;

int main()
{	
	message_t msg;
	struct vfs_request* rq = (struct vfs_request*) &msg.message;
	Drive rootdrive;
	
	int retval = vfs_mount_ramdisk("/drives/ramfs", VFS_MODE_RW);
	if (retval == SIGNAL_FAIL)
	{
		perror("[ RAMFS ] Could not mount device!");
		return -1;
	}

	Directory root;
	/*debug_printf("Self test\n");
	Directory* dir = rootdrive.getRoot();
	Directory* test = static_cast<Directory*>(dir->find("/"));
	assert(dir == test);

	dir->mkdir("test");
	test = static_cast<Directory*>(dir->find("/test"));
	assert(test != NULL);

	File* testFile = static_cast<File*>(dir->open("/file.txt", VFS_MODE_WO));
	assert(testFile != NULL);

	testFile = static_cast<File*>(dir->open("/test/file.txt", VFS_MODE_WO));
	assert(testFile != NULL);

	testFile = static_cast<File*>(dir->open("/file.txt", VFS_MODE_RO));
	assert(testFile != NULL);

	const char* str = "LALALAGAGAG";
	testFile->write((void*) str, strlen(str), 0);

	debug_printf("Wrote to file: %s\n", testFile->content);
	
	testFile = static_cast<File*>(dir->open("/filex.txt", VFS_MODE_RO));
	assert(testFile == NULL);*/
	
	debug_printf("[ RAMFS ] Started.\n");
	while(1)
	{
		while (receive_message(&msg, MESSAGE_ANY) != MESSAGE_RECEIVED)
				sleep(10);

		switch (msg.signal)
		{
			case FS_SIGNAL_OPEN:
			{
				File* f = root.open(rq->path, (VFS_OPEN_MODES) rq->mode);
				if(!f)
					msg.signal = SIGNAL_FAIL;
				else
					msg.signal = SIGNAL_OK;
				
				send_message(&msg, msg.sender);
			}
			break;

			case FS_SIGNAL_STAT:
			{
				
				struct stat* stat = (struct stat*) &msg.message;
				File* f = dynamic_cast<File*>(root.find(rq->path));
				
				if(!f)
				{
					msg.signal = SIGNAL_FAIL;
					send_message(&msg, msg.sender);
					break;
				}

				*stat = f->info;
				stat->st_dev = msg.receiver;
				
				msg.signal = SIGNAL_OK;
				send_message(&msg, msg.sender);
			}
			break;

			case FS_SIGNAL_READ:
			{
				File* f = static_cast<File*>(root.find(rq->path));
				pid_t sender = msg.sender;
				size_t size = 0;
				
				if(!f || (rq->offset > f->info.st_size))
				{
					msg.signal = SIGNAL_FAIL;
					send_message(&msg, msg.sender);
					break;
				}
				
				size = std::min(rq->offset + msg.size, f->info.st_size - rq->offset);
				write_message_stream(f->content + rq->offset, size, sender);
		    }
			break;

			case FS_SIGNAL_WRITE:
			{
				File* f = static_cast<File*>(root.find(rq->path));
				pid_t sender = msg.sender;
				
				if(!f)
				{
					msg.signal = SIGNAL_FAIL;
					send_message(&msg, msg.sender);
					break;
				}
				
				f->alloc(msg.size, rq->offset);
				read_message_stream(f->content, msg.size, sender);
			}
			break;

			case FS_SIGNAL_OPEN_DIR:
			{
				rootdrive.opendir(*rq);
			}
			break;

			case VFS_SIGNAL_READ_DIR:
			{
				rootdrive.readdir(*rq);
			}
			break;

			default:
				debug_printf("[ RAMFS ] Unknown signal %d from %d\n",
							 msg.signal, msg.sender);
		}
	}

	return 0;
}
