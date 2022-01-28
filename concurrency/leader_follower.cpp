#include <future>
#include <mutex>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <iostream>
#include <string>
#include <vector>

void leaderFollower() {
    boost::interprocess::interprocess_semaphore leaderQueue(0);
    boost::interprocess::interprocess_semaphore followerQueue(0);
    std::vector<std::future<void> > v;

    auto launcher = [&] (bool isLeader) {
        std::string self = isLeader ? "Leader" : "Follower";
        std::string other = isLeader ? "Follower" : "Leader";
        boost::interprocess::interprocess_semaphore& selfQueue = isLeader ? leaderQueue : followerQueue;
        boost::interprocess::interprocess_semaphore& otherQueue = isLeader ? followerQueue : leaderQueue;

        otherQueue.post();
        selfQueue.wait();
        printf("%s is dancing with %s\n", self.c_str(), other.c_str());
    };

    for (int i = 0; i < 10; i++) {
        std::future<void> temp = std::async(std::launch::async, launcher, i % 2 == 0);
        v.push_back(std::move(temp));
    }

    for (int i = 0; i < 10; i++) {
        v[i].get();
    }

    printf("Done\n");


}

int main() {
    leaderFollower();
}