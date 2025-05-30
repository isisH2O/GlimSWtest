#include <string>
#include <vector>

using namespace std;

int solution(int n, int k) {
    // 서비스로 받는 음료수 개수: 양꼬치 10인분당 1개
    int service = n / 10;

    // 실제 결제하는 음료수는 전체에서 서비스 빼기
    int paidDrinks = k - service;

    // 총 비용 계산
    int total = (n * 12000) + (paidDrinks * 2000);

    return total;
}
