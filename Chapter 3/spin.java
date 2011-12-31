/*
ID: faorien2
PROG: spin
LANG: JAVA
*/

import java.io.*;
import java.util.*;

class spin {
  public static void main(String[] args) throws IOException {
    (new spin()).solve();
  }

  public void solve() throws IOException {
    BufferedReader fin = new BufferedReader(new FileReader("spin.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("spin.out")));

    Wheel wheels[] = new Wheel[5];

    // always exactly 5 wheels
    for (int i = 0; i < 5; ++i) {
      StringTokenizer st = new StringTokenizer(fin.readLine());
      wheels[i] = new Wheel(Integer.parseInt(st.nextToken()));

      int wedges_num = Integer.parseInt(st.nextToken());

      for (int j = 0; j < wedges_num; ++j) {
        int start_angle = Integer.parseInt(st.nextToken());
        int angle_size = Integer.parseInt(st.nextToken());
        wheels[i].addWedge(start_angle, (start_angle + angle_size) % 360);
      }
    }

    int result = -1;
    // incorrect naming, should have been current time in seconds
    int current_angle = 0;

    do {
      boolean ok = true;

      for (int angle = 0; angle < 360; ++angle) {
        ok = true;

        for (int i = 0; i < 5; ++i) {
          if (!wheels[i].isThereWedgeAt(angle)) {
            ok = false;
            break;
          }
        }

        if (ok)
          break;
      }

      if (ok) {
        result = current_angle;
        break;
      }

      for (int i = 0; i < 5; ++i)
        wheels[i].rotate();

      ++current_angle;
    } while (current_angle < 360);

    fout.println(result == -1 ? "none" : result);

    fout.close();
    System.exit(0); // don't omit this
  }


  private class Wheel {
    private int rotation_speed, current_angle;
    private List<Pair<Integer,Integer>> wedges = new ArrayList<Pair<Integer,Integer>>();

    public Wheel(int rotation_speed) {
      this.rotation_speed = rotation_speed;
      this.current_angle = 0;
    }

    public void rotate() {
      current_angle = (current_angle + rotation_speed) % 360;
    }

    public void addWedge(int start_angle, int end_angle) {
      wedges.add(new Pair<Integer,Integer>(start_angle, end_angle));
    }

    // is there a wedge at the given angle given current angle of the wheel
    public boolean isThereWedgeAt(int angle) {
      for (int i = 0; i < wedges.size(); ++i) {
        int start = (wedges.get(i).first + current_angle) % 360;
        int end = (wedges.get(i).second + current_angle) % 360;

        if (start <= end) {
          if (angle >= start && angle <= end)
            return true;
        } else {
          if (angle >= start || angle <= end)
            return true;
        }
      }

      return false;
    }
  }

  private class Pair<X,Y> {
    public final X first;
    public final Y second;

    public Pair(X first, Y second) {
      this.first = first;
      this.second = second;
    }

    @Override
      public int hashCode() {
        return first.hashCode() ^ second.hashCode();
      }

    @Override
      public boolean equals(Object o) {
        if (o == null)
          return false;

        if (!(o instanceof Pair))
          return false;

        Pair other_pair = (Pair) o;
        return this.first.equals(other_pair.first) && this.second.equals(other_pair.second);
      }
  }
}
