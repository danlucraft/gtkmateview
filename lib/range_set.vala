
using GLib;
using Gee;

// This data structure stores sets of ranges 
// like 1, 4-9, 10, 12, 15-20
public class RangeSet : Object {
	public struct IntPair {
		public int a;
		public int b;
		public IntPair(int x, int y) {
			a = x;
			b = y;
		}
	}

	public ArrayList<IntPair?> ranges;

	public int length() {
		return (int) ranges.size;
	}

	public int size() {
		int sizec = 0;
		foreach (IntPair? p in ranges)
			sizec += p.b - p.a + 1;
		return sizec;
	}

	public void add(int a, int b) {
		bool merged = false;
		int ix = 0;
		int remove_ix;
		IntPair add_p;
		IntPair? p, p2;
		for (int i = 0; i < ranges.size-1; i++) {
			p = ranges[i];
			p2 = ranges[i+1];
			if (a > p.b && !merged) {
				ix++;
			}
			if (a >= p.a && a <= p.b && b > p.b) {
				stdout.printf("asdf: %d\n", b);
				remove_ix = ix;
				add_p = IntPair(p.a, b);
				merged = true;
			}
			if (b >= p.a && b <= p.b && a < p.a) {
				p.a = a;
				remove_ix = ix;
				add_p = IntPair(a, p.b);
				merged = true;
			}
		}
		if (!merged) {
			IntPair? p = IntPair(a, b);
			ranges.insert(ix, p);
		}
		else {
			ranges.remove_at(remove_ix);
			ranges.insert(ix, add_p);
		}
	}

	public string present() {
		var sb = new StringBuilder("");
		foreach (IntPair? p in ranges) {
			if (p.b - p.a == 0) {
				sb.append(p.a.to_string());
				sb.append(", ");
			}
			else {
				sb.append(p.a.to_string());
				sb.append("-");
				sb.append(p.b.to_string());
				sb.append(", ");
			}
		}
		return sb.str;
	}

	construct {
		ranges = new ArrayList<IntPair?>();
	}

	public RangeSet() {
	}
}