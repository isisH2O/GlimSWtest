#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> arr, vector<bool> flag) {
    vector<int> answer;

    // flag 배열의 각 요소를 순서대로 확인
    for (int i = 0; i < flag.size(); i++) {
        if (flag[i]) {
            // flag[i]가 true인 경우:
            // arr[i] 값을 arr[i] * 2번 answer에 추가
            for (int j = 0; j < arr[i] * 2; j++) {
                answer.push_back(arr[i]);
            }
        } else {
            // flag[i]가 false인 경우:
            // answer의 마지막 arr[i]개 요소를 제거
            for (int j = 0; j < arr[i]; j++) {
                // 문제 조건상 항상 뺄 수 있는 만큼만 주어진다 함
                answer.pop_back();
            }
        }
    }

    return answer;
}
