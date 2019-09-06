// 이거 못함......
// 다 했는데, 수가 10의자리부터 못함....

#include <string>
#include <vector>

using namespace std;

string solution(string s) {

	bool isMinus{ false };
	bool isOn{ false };

	int lowValue, highValue;

	for (auto i : s) {
		if (i == ' ') {
			isMinus = false;
		}
		else if (i == '-') {
			isMinus = true;
		}
		else {
			if (!isOn) {
				if (!isMinus) {
					highValue = atoi(&i);
					lowValue = atoi(&i);
				}
				else {
					highValue = -1 * atoi(&i);
					lowValue = -1 * atoi(&i);
					isMinus = false;
				}
				isOn = true;
			}
			else {
				if (!isMinus) {
					if (atoi(&i) > highValue) {
						highValue = atoi(&i);
					}
					else if (atoi(&i) < lowValue) {
						lowValue = atoi(&i);
					}
				}
				else {
					if (-1 * atoi(&i) > highValue) {
						highValue = -1 * atoi(&i);
					}
					else if (-1 * atoi(&i) < lowValue) {
						lowValue = -1 * atoi(&i);
					}

					isMinus = false;
				}
			}
		}
	}


	string answer{};

	answer += std::to_string(lowValue);
	answer += ' ';
	answer += std::to_string(highValue);

	return answer;
}
