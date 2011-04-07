#ifndef _FASTCGI_REQUEST_CACHE_FILE_CACHE_H_
#define _FASTCGI_REQUEST_CACHE_FILE_CACHE_H_

#include <string>

#include "fastcgi2/component.h"
#include "details/request_cache.h"
#include "details/server.h"

namespace fastcgi
{

class Logger;

struct DelayTask {
	DelayTask() {}
	DelayTask(const std::string &key_str, int num_retries) :
		key(key_str), retries(num_retries)
	{}
	std::string key;
	int retries;
};

class FileRequestCache : virtual public RequestCache, virtual public Component, public Server {
public:
	FileRequestCache(ComponentContext *context);
	virtual ~FileRequestCache();

	virtual void onLoad();
	virtual void onUnload();

	virtual DataBuffer create();
	virtual void save(Request *request, time_t delay);
	virtual boost::uint32_t minPostSize() const;

protected:
	virtual const Globals* globals() const;
	virtual Logger* logger() const;

private:
	void handle();
	bool saveRequest(Request *request, const std::string &key, std::string &new_key);
	std::string getKey(Request *request);
	std::string getStoredKey(Request *request);
	std::string generateUniqueKey();
	void eraseActive(const std::string &key);
	void insertWaiting(time_t delay, const std::string &key, int retries);
	DataBuffer createFileBuffer(const std::string &key);
	std::string createHardLink(const std::string &key);
	void stop();

private:
	const Globals *globals_;
	Logger *logger_;

	std::string cache_dir_;
	boost::uint64_t window_;
	boost::uint32_t max_retries_;
	boost::uint32_t min_post_size_;
	std::multimap<time_t, DelayTask> waiting_;
	std::map<std::string, int> active_;
	boost::mutex active_mutex_, waiting_mutex_;
	std::auto_ptr<boost::thread> thread_;

	bool stopped_;
	boost::condition condition_;
	boost::mutex mutex_;
};

} // namespace fastcgi

#endif // _FASTCGI_REQUEST_CACHE_FILE_CACHE_H_
