#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, int k) {
    int answer = 0; // answer = sum 역할을 하는 변수

    int m = board.size();       // 행 개수
    int n = board[0].size();    // 열 개수

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // board[i][j]는 i + j가 k 이하일 때만 더함
            if (i + j <= k) answer += board[i][j];
        }
    }

    return answer;
}
