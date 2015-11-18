//http://st.xorian.net/blog/2012/08/go-style-channel-in-c/
#include <list>
#include <thread>
#include <mutex>
#pragma message ("Channel is defined")
using namespace std;
template<class item>
class Channel {
private:
	std::list<item> queue;
	std::mutex m;
	std::condition_variable cv;
	bool closed;
public:
	Channel() : closed(false) { }
	//Closes the channel
	void close() {
		std::unique_lock<std::mutex> lock(m);
		closed = true;
		cv.notify_all();
	}
	//Check's if the channel is closed
	bool is_closed() {
		std::unique_lock<std::mutex> lock(m);
		return closed;
	}
	//Put's the item into the stack last
	void put(const item &i) {
		std::unique_lock<std::mutex> lock(m);
		if (closed)
			throw std::logic_error("put to closed channel");
		queue.push_back(i);
		cv.notify_one();
	}
	//Get's the item first put into the stack, removing from it in the process
	//Using the wait parameter allows the use of a 'select' style of channel
	//processing
	bool get(item &out, bool wait = true) {
		std::unique_lock<std::mutex> lock(m);
		if (wait)
			cv.wait(lock, [&]() { return closed || !queue.empty(); });
		if (queue.empty())
			return false;
		out = queue.front();
		queue.pop_front();
		return true;
	}
};