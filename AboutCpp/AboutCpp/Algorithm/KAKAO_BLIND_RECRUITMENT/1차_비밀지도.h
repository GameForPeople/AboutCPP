#include <string>
#include <vector>

using namespace std;

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {

	vector<string> answer;
	int buffer, subBuffer;

	int maxValue = 1;
	int maxBuffer;

	for (int i = 1; i < n; ++i)
		maxValue *= 2;

	for (int i = 0; i < n; ++i)
	{
		buffer = arr1[i] |= arr2[i];
		answer.emplace_back("");

		if (buffer == 0)
		{
			for (int j = 0; j < n; ++j)
			{
				answer[i] += " ";
			}
		}
		else
		{
			maxBuffer = maxValue;

			while (buffer != 0)
			{
				if (maxBuffer / 2 - 1 < buffer) {
					subBuffer = buffer % 2;
					buffer /= 2;

					if (subBuffer == 1)
						answer[i] = "#" + answer[i];
					else
						answer[i] = " " + answer[i];
				}
				else {
					answer[i] = " " + answer[i];
				}
				maxBuffer /= 2;
			}
		}
	}

	return answer;
}