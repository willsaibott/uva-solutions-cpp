/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

template <class T = size_t>
T getInput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

struct Message {
  size_t id;
  size_t size;
  size_t begin;

  bool operator<(const Message& other) const {
    return id < other.id;
  }
};

struct Packet {
  size_t message_id;
  size_t begin;
  size_t end;


  size_t get_size() const {
    return end - begin + 1;
  }
};

struct SortByBegin {
  bool operator()(const Packet& p1, const Packet& p2) const {
    return p1.begin < p2.begin;
  }
};

std::istream& operator >>(std::istream& iss, Packet& packet) {
  return iss >> packet.message_id >> packet.begin >> packet.end;
}

class Buffer {
  std::map<size_t, std::set<Packet, SortByBegin>> buffered;
  const std::vector<Message>& original_messages;
  std::array<size_t, 10>             message_left_from = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  std::vector<Message>::const_iterator next_msg;
  size_t size{ 0 };

  void verify_if_buffered_packets_can_be_removed(size_t msg_id) {
    auto& buffer_for_packet = buffered[msg_id];
    auto& msg_from = message_left_from[msg_id];
    while (!buffer_for_packet.empty() && buffer_for_packet.begin()->begin == msg_from) {
      msg_from = buffer_for_packet.begin()->end + 1;
      size -= buffer_for_packet.begin()->get_size();
      buffer_for_packet.erase(buffer_for_packet.begin());
    }

    if (msg_from > next_msg->size) {
      next_msg++;
      if (next_msg != original_messages.end()) {
        verify_if_buffered_packets_can_be_removed(next_msg->id);
      }
    }
  }

  public:

  Buffer(const std::vector<Message>& messages) : original_messages{ messages } {
    next_msg = messages.begin();
  }

  Buffer&
  add(const Packet& packet) {
    if (packet.message_id == next_msg->id) {
      if (message_left_from[packet.message_id] == packet.begin) {
        message_left_from[packet.message_id] = packet.end + 1;
        verify_if_buffered_packets_can_be_removed(packet.message_id);
        return *this;
      }
    }

    size += packet.get_size();
    buffered[packet.message_id].insert(packet);

    return *this;
  }

  size_t get_size() const {
    return size;
  }

};

class Solution {

public:

  size_t solve(std::vector<Message> messages, const std::vector<Packet>& packets) {
    size_t min_needed_buffer_size = std::numeric_limits<size_t>::max();

    do {
      Buffer buffer(messages);
      std::size_t buffer_size = 0ul;
      for (auto& packet : packets) {
        buffer_size = std::max(buffer_size, buffer.add(packet).get_size());
      }
      min_needed_buffer_size = std::min(min_needed_buffer_size, buffer_size);
    } while (std::next_permutation(messages.begin(), messages.end()));

    return min_needed_buffer_size;
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t kase = 1;
  std::size_t total_messages, total_packets;

  while (cin >> total_messages >> total_packets && total_messages && total_packets) {
    std::vector<Message> messages;
    std::vector<Packet> packets;
    Solution solution;

    for (size_t ii = 0ul; ii < total_messages; ii++) {
      messages.emplace_back(Message{ ii + 1, getInput(), 1 });
    }

    for (size_t jj = 0ul; jj < total_packets; jj++) {
      packets.emplace_back(getInput<Packet>());
    }

    std::cout << "Case " << kase++ << ": " << solution.solve(messages, packets) << "\n\n";
  }

  return(0);
}