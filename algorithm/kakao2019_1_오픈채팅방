#inclue <string>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;
map<string, string> id; //id, name
vector<pair<int, string>> inout; // 1/2(enter/leave), id
vector<string> split(string str, char delimiter) { //split함수
	vector<string> internal;
	stringstream ss(str);
	string temp;
	while (getline(ss, temp, delimiter)) {
		internal.push_back(temp);
	}
	return internal;
}

vector<string> solution(vector<string> record) {
	vector<string> answer; // 최종 답안
	int ssize = record.size();
	for (int i = 0; i < ssize; i++) {
		vector<string> str = split(record[i], ' ');
		if (!str[0].compare("Enter")) {
			id[str[1]] = str[2];
			inout.push_back(make_pair(1, str[1]));
		}
		else if (!str[0].compare("Leave")) 
			inout.push_back(make_pair(2, str[1]));
		else 
			id[str[1]] = str[2];
		
	}
	ssize = inout.size();
	for (int i = 0; i<ssize; i++) {
		string name = id[inout[i].second];
		if (inout[i].first == 1)
			answer.push_back(name + "님이 들어왔습니다.");
		else
			answer.push_back(name + "님이 나갔습니다.");
	}
	return answer;
}
