#include "Drive.h"
#include <algorithm>
#include <dayos.h>
#include <string.h>

File* Drive::open(vfs_request& rq)
{

}

int Drive::read(vfs_request& rq)
{

}

int Drive::write(vfs_request& rq)
{

}

Directory* Drive::opendir(vfs_request& rq)
{

}

Directory* Drive::readdir(vfs_request& rq)
{

}


Node* Directory::find(std::string::iterator name, std::string& full)
{
	if(name == full.end())
		return NULL;

	// For a root dir
	if(!strcmp(&*name, "/"))
		return static_cast<Node*>(this);
	
	int curIdx = full.end() - name;
	int idx = full.find("/", curIdx);
	if(idx == -1)
	{
		// If we are in the root directory, skip the first char ('/')
		if(name == full.begin())
			name++;
		
		auto node = content.find(&*name);
		if(node == content.end())
			return NULL;

		return node->second;
	}

	auto node = content.find(full.substr(curIdx, idx));
	if(node == content.end())
		return NULL;

	return find(full.begin() + idx + 1, full);
}

File* Directory::open(const char* name, VFS_OPEN_MODES mode)
{
	std::string path(name);
	int idx = path.find_last_of("/");

	if (idx == -1)
		return NULL;

	std::string fname = path.substr(idx + 1);
	path.erase(idx);

	if (path.empty() && !fname.empty())
		path = "/";

	Directory* dir = dynamic_cast<Directory*>(find(path.c_str()));
	auto iter = dir->content.find(fname);

	if (iter == dir->content.end() && mode & VFS_MODE_WO)
	{
		File* f = new File();
		f->name = fname;
		dir->content[fname] = f;
		return f;
	}
	else if (iter != dir->content.end() && mode & VFS_MODE_WO)
	{
		File* f = new File();
		delete iter->second;

		f->name = fname;
		dir->content[fname] = f;
		return f;
	}
	else if (iter == dir->content.end())
	{
		return NULL;
	}

	return dynamic_cast<File*>(iter->second);
}

void File::write(void* data, size_t sz, size_t offset)
{
	alloc(sz, offset);	
	memcpy(content + offset, data, sz);
}

void File::alloc(size_t sz, size_t offset)
{
	size_t newsize = sz + offset;
	if (newsize > info.st_size)
	{
		info.st_size = newsize;
		content = (char*) realloc(content, newsize);
	}
}

size_t File::read(void* data, size_t sz, size_t offset)
{
	if(!data)
		return 0;

	size_t newsize = (sz + offset > info.st_size) ? info.st_size - offset : sz;
	memcpy(data, content + offset, sz);
	return newsize;
}
