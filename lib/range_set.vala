
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

	public bool is_empty() {
		return (ranges.size == 0);
	}

	public void add(int a, int b) {
		bool merged = false;
		int insert_ix = 0;
		IntPair n = IntPair(a, b);
		IntPair? p, p2;
		foreach (var p in ranges) {
			if (p.a < n.a)
				insert_ix++;
		}
		ranges.insert(insert_ix, n);
		merge(insert_ix);
	}

	public void merge(int ix) {
		IntPair? n = ranges[ix];
		// stdout.printf("merge(%d, %d..%d)\n", ix, n.a, n.b);
		if (ix > 0) {
			// stdout.printf("ix > 0\n");
			IntPair? x = ranges[ix-1];
			// stdout.printf("x: %d..%d, n: %d..%d\n", x.a, x.b, n.a, n.b);
			if (n.a <= x.b+1) {
				ranges.remove_at(ix);
				x.b = max(x.b, n.b);
				ranges[ix-1] = x;
				ix--;
				n = ranges[ix];
			}
		}
		if (ix < ranges.size-1) {
			// stdout.printf("ix < %d\n", ranges.size-1);
			IntPair? y = ranges[ix+1];
			while (ix < ranges.size-1 && n.b >= y.a-1) {
				// stdout.printf("n: %d..%d, y: %d..%d\n", n.a, n.b, y.a, y.b);
				y.a = min(n.a, y.a);
				if (n.b > y.b)
					y.b = n.b;
				ranges[ix+1] = y;
				ranges.remove_at(ix);
				if (ix < ranges.size-1)
					y = ranges[ix+1];
			}
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
				sb.append("..");
				sb.append(p.b.to_string());
				sb.append(", ");
			}
		}
		return sb.str;
	}

	public int max(int a, int b) {
		if (a > b)
			return a;
		else
			return b;
	}

	public int min(int a, int b) {
		if (a < b)
			return a;
		else
			return b;
	}
	
	construct {
		ranges = new ArrayList<IntPair?>();
	}

	public RangeSet() {
	}
}