#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> dots) {
    // 첫 번째 점의 좌표로 최대/최소 초기화
    int leftX = dots[0][0];
    int rightX = dots[0][0];
    int bottomY = dots[0][1];
    int topY = dots[0][1];

    // 나머지 점들과 비교하며 최대/최소 갱신
    for (int i = 1; i < 4; i++) {
        if (dots[i][0] < leftX) leftX = dots[i][0];
        if (dots[i][0] > rightX) rightX = dots[i][0];
        if (dots[i][1] < bottomY) bottomY = dots[i][1];
        if (dots[i][1] > topY) topY = dots[i][1];
    }

    // 넓이는 가로 길이 * 세로 길이
    int width = rightX - leftX;
    int height = topY - bottomY;

    int answer = width * height;
    return answer;
}
