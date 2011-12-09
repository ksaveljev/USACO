/*
ID: faorien2
PROG: kimbits
LANG: JAVA
*/

import java.io.*;
import java.util.*;
import java.math.BigInteger;

class kimbits {
  private static BigInteger factorial(int n) {
    if (n == 0 || n == 1)
      return BigInteger.ONE;

    return (BigInteger.valueOf(n)).multiply(factorial(n-1));
  }

  private static BigInteger number_of_permutations(int n, int bits_set) {
    return factorial(n).divide(factorial(bits_set).multiply(factorial(n-bits_set)));
  }

  public static void main(String[] args) throws IOException {
    BufferedReader fin = new BufferedReader(new FileReader("kimbits.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("kimbits.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());

    int N = Integer.parseInt(st.nextToken());
    int L = Integer.parseInt(st.nextToken());
    //int I = Integer.parseInt(st.nextToken());
    BigInteger I = new BigInteger(st.nextToken());

    BigInteger dp[][] = new BigInteger[N+1][L+1];

    for (int i = 0; i <= N; i++)
      for (int j = 0; j <= L; j++)
        dp[i][j] = BigInteger.ONE;

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= L; j++) {
        if (j > i)
          dp[i][j] = dp[i][j-1];
        else
          dp[i][j] = dp[i][j-1].add(number_of_permutations(i, j));
      }
    }

    while (N > 0) {
      int result = I.compareTo(dp[N-1][L]);

      if (L == 0) {
        fout.print(0);
      } else if (result == 1) {
        fout.print(1);
        I = I.subtract(dp[N-1][L]);
        L -= 1;
      } else {
        fout.print(0);
      }

      N -= 1;
    }
    fout.println();

    fout.close();
    System.exit(0); // don't omit this
  }
}
