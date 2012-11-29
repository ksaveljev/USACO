/*
ID: faorien2
PROG: shopping
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;

#define REP(i, b, n) for (int i = b; i < n; i++)
#define rep(i, n) REP(i, 0, n)
#define REPS(i, b, n) for (int i = b; i <= n; i++)
#define reps(i, n) REPS(i, 0, n)

typedef struct _purchase {
    int product_code;
    int number_of_items;
    int product_price;
} purchase;

int offer[100][1000];
int offer_price[100];
int dp[6][6][6][6][6];
purchase purchases[5];

int main() {
    int number_of_special_offers;
    int number_of_products_offered;
    int number_of_items;
    int product_code;
    int number_of_products_to_purchase;
    int product_price;

    ofstream fout("shopping.out");
    ifstream fin("shopping.in");

    fin >> number_of_special_offers;

    rep (i, number_of_special_offers) {
        fin >> number_of_products_offered;

        rep (j, number_of_products_offered) {
            fin >> product_code >> number_of_items;
            offer[i][product_code] = number_of_items;
        }

        fin >> offer_price[i];
    }

    fin >> number_of_products_to_purchase;

    rep (i, number_of_products_to_purchase) {
        fin >> purchases[i].product_code >> purchases[i].number_of_items >> purchases[i].product_price;
    }

    dp[0][0][0][0][0] = 0;

    reps (i, purchases[0].number_of_items) {
        reps (j, purchases[1].number_of_items) {
            reps (k, purchases[2].number_of_items) {
                reps (m, purchases[3].number_of_items) {
                    reps (n, purchases[4].number_of_items) {
                        dp[i][j][k][m][n] = purchases[0].product_price * i +
                                            purchases[1].product_price * j +
                                            purchases[2].product_price * k +
                                            purchases[3].product_price * m +
                                            purchases[4].product_price * n;

                        rep (o, number_of_special_offers) {
                            int i1 = i - offer[o][purchases[0].product_code];
                            int j1 = j - offer[o][purchases[1].product_code];
                            int k1 = k - offer[o][purchases[2].product_code];
                            int m1 = m - offer[o][purchases[3].product_code];
                            int n1 = n - offer[o][purchases[4].product_code];

                            if (i1 < 0 || j1 < 0 || k1 < 0 || m1 < 0 || n1 < 0)
                                continue;

                            int price = dp[i1][j1][k1][m1][n1] + offer_price[o];

                            if (price < dp[i][j][k][m][n]) {
                                dp[i][j][k][m][n] = price;
                            }
                        }
                    }
                }
            }
        }
    }

    fout << dp[purchases[0].number_of_items][purchases[1].number_of_items][purchases[2].number_of_items][purchases[3].number_of_items][purchases[4].number_of_items] << endl;

    return 0;
}
