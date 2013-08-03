#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <cassert>
#include <cmath>

using namespace std;

#define NDEBUG
#define NINFO

typedef long long int lli;

const lli INF = 987654321;
const int MAX_N = 1000000;

struct Line {
    lli offset;
    lli slope;
};

struct Segment {
    Line e;
    lli begin;
    lli end;
};

bool operator <(Line a, Line b) {
    return a.slope < b.slope;
}

struct line_intersect_result {
    bool intersect;
    lli x;
};

struct line_set {
    // only those that form the convex polygon
    map< lli, Line > line_by_endpoint;
    map< lli, lli > endpoint_by_slope;

    inline void insert_at(Line e, lli endpoint) {
        #ifndef NDEBUG
        printf("Inserting line (%lli, %lli) at endpoint %lli.\n", e.offset, e.slope, endpoint);
        #endif
        map< lli, Line >::iterator it = line_by_endpoint.find(endpoint);
        if (it != line_by_endpoint.end()) {
            lli ye = e.offset + endpoint * e.slope;
            lli ym = it->second.offset + endpoint * it->second.slope;

            if (ye < ym || (ye == ym && e.slope < it->second.slope)) {
                #ifndef NDEBUG
                printf("Not replacing existing line.\n");
                #endif
                return;
            }
            else {
                #ifndef NDEBUG
                printf("Replacing existing line.\n");
                #endif
                endpoint_by_slope.erase(it->second.slope);
                line_by_endpoint.erase(endpoint);
            }
        }
        line_by_endpoint[endpoint] = e;
        endpoint_by_slope[e.slope] = endpoint;

        #ifndef NDEBUG
        assert(line_by_endpoint.size() == endpoint_by_slope.size());
        printf("Line set now has %i lines.\n", (int)line_by_endpoint.size());
        print();
        #endif
    }

    inline void erase_at(map< lli, lli >::iterator it) {
        #ifndef NDEBUG
        printf("Erasing line: (%lli, %lli)\n", line_by_endpoint[endpoint_by_slope[it->first]].offset, it->first);
        #endif

        endpoint_by_slope.erase(it);
        line_by_endpoint.erase(it->second);

        #ifndef NDEBUG
        printf("Line set now has %i lines.\n", (int)line_by_endpoint.size());
        print();
        #endif
    }

    Segment segment_by_iterator(map< lli, lli >::iterator it) {
        Segment ret;

        ret.e = line_by_endpoint[it->second];
        ret.begin = it->second;

        lli slope = it->first;

        ++it;

        if (it == endpoint_by_slope.end()) {
            ret.end = INF;
        }
        else {
            ret.end = it->second;
        }

        /*
        printf("Construct segment from line (%lli, %lli). Segment endpoints (%lli, %lli). Reported slope %lli.\n",
               ret.e.offset,
               ret.e.slope,
               ret.begin,
               ret.end,
               slope);
        */

        return ret;
    }

    void insert(Line e) {
        assert(e.slope <= 0);

        #ifndef NINFO
        printf("Inserting line (%lli + %llix).\n", e.offset, e.slope);
        #endif

        #ifndef NDEBUG
        printf("Checking for parallels.\n");
        #endif

        map< lli, lli >::iterator parallel = endpoint_by_slope.find(e.slope);
        if (parallel != endpoint_by_slope.end()) {
            if (line_by_endpoint[parallel->second].offset > e.offset) {
                #ifndef NDEBUG
                printf("Parallel line suboptimal everywhere. Discarding.\n");
                #endif
                return;
            }
            #ifndef NDEBUG
            else {
                printf("Parallel line better than previous.\n");
            }
            #endif
        }

        line_intersect_result r;

        if (line_by_endpoint.empty()) {
            insert_at(e, -INF);
            #ifndef NDEBUG
            printf("First line in universe; adding unconditionally.\n");
            #endif
            return;
        }

        map< lli, lli >::iterator it = endpoint_by_slope.upper_bound(e.slope);

        if (it != endpoint_by_slope.end()) {
            #ifndef NDEBUG
            printf("Mid-point found.\n");
            printf("Mid-point below new line in existing convex is: %lli.\n", it->second);
            #endif
            lli x0 = it->second;
            lli ym0 = find(x0);
            lli ye0 = e.offset + x0 * e.slope;
            lli x1;
            if (x0 > -INF) {
                x1 = x0 - 1;
            }
            else {
                x1 = x0;
            }
            lli ym1 = find(x1);
            lli ye1 = e.offset + x1 * e.slope;
            #ifndef NDEBUG
            printf("ym0 = %lli, ye0 = %lli.\n", ym0, ye0);
            #endif

            if (ym0 >= ye0 && ym1 >= ye1) {
                // line is never optimal, discard
                #ifndef NDEBUG
                printf("Line is everywhere suboptimal (ym = %lli >= ye = %lli).\n", ym0, ye0);
                #endif
                return;
            }
        }
        else {
            #ifndef NDEBUG
            printf("No mid-point found. Line is asymptotically optimal at infinity.\n");
            #endif
        }

        map< lli, lli >::iterator jt(it), kt(it);
        bool has_prev = true;

        if (kt == endpoint_by_slope.begin()) {
            has_prev = false;
        }
        else {
            --kt;
        }

        #ifndef NDEBUG
        printf("Iterating over next lines.\n");
        #endif
        if (jt != endpoint_by_slope.end()) {
            #ifndef NDEBUG
            printf("First next line has slope %lli.\n", jt->first);
            printf("First next line has endpoint %lli.\n", jt->second);
            printf("First next line is: %lli, %lli.\n", line_by_endpoint[jt->second].offset, line_by_endpoint[jt->second].slope);
            #endif
            r = line_segment_intersect(e, segment_by_iterator(jt));
            #ifndef NDEBUG
            printf("First next line has slope %lli.\n", jt->first);
            printf("First next line has endpoint %lli.\n", jt->second);
            printf("First next line is: %lli, %lli.\n", line_by_endpoint[jt->second].offset, line_by_endpoint[jt->second].slope);
            #endif
        }
        while (jt != endpoint_by_slope.end() && !r.intersect) {
            #ifndef NDEBUG
            printf(".\n");
            #endif
            erase_at(jt++);
            if (jt != endpoint_by_slope.end()) {
                r = line_segment_intersect(e, segment_by_iterator(jt));
            }
        }
        if (jt != endpoint_by_slope.end()) {
            #ifndef NDEBUG
            printf("Intersection found.\n");
            #endif
            Line chopped(line_by_endpoint[jt->second]);
            erase_at(jt);
            insert_at(chopped, r.x);
        }
        else {
            #ifndef NDEBUG
            printf("New line is asymptotically optimal at +∞.\n");
            #endif
        }
        #ifndef NDEBUG
        printf("Iterating over previous lines.\n");
        #endif
        bool done = false, optimal = false;
        if (!has_prev) {
            done = true;
            optimal = true;
        }
        else {
            #ifndef NDEBUG
            printf("First previous line is: %lli, %lli.\n", line_by_endpoint[kt->second].offset, line_by_endpoint[kt->second].slope);
            #endif
            r = line_segment_intersect(e, segment_by_iterator(kt));
        }
        if (kt == endpoint_by_slope.begin()) {
            done = true;
        }
        while (has_prev && !r.intersect) {
            // printf(".\n");
            map< lli, lli >::iterator mt(kt);
            if (!done) {
                --mt;
            }
            erase_at(kt);
            #ifndef NDEBUG
            printf("Erased.\n");
            print();
            #endif
            if (done) {
                #ifndef NDEBUG
                printf("We are done and exiting loop at optimal condition.\n");
                #endif
                optimal = true;
                break;
            }
            kt = mt;
            if (kt == endpoint_by_slope.begin()) {
                done = true;
            }
            #ifndef NDEBUG
            printf("Performing intersection.\n");
            #endif
            r = line_segment_intersect(e, segment_by_iterator(kt));
        }
        #ifndef NDEBUG
        printf("Done with previous lines.\n");
        #endif
        if (optimal) {
            // no previous intersections could be determined; the line is optimal asymptotically at -infinity
            #ifndef NDEBUG
            printf("New line is asymptotically optimal at -∞.\n");
            #endif
            insert_at(e, -INF);
        }
        else {
            insert_at(e, r.x);
        }
    }

    lli find(lli x) {
        if (line_by_endpoint.empty()) {
            return 0;
        }

        map< lli, Line >::iterator it = line_by_endpoint.upper_bound(x);

        --it;

        return it->second.offset + x * it->second.slope;
    }

    line_intersect_result line_segment_intersect(Line a, Segment b) {
        line_intersect_result res;

        res.intersect = true;
        #ifndef NDEBUG
        printf("Intersecting (%lli, %lli) with (%lli, %lli).\n", a.offset, a.slope, b.e.offset, b.e.slope);
        #endif
        if (a.slope == b.e.slope) {
            #ifndef NDEBUG
            printf("Lines are parallel or identical.\n");
            #endif
            res.intersect = false;
            return res;
        }
        res.x = ceil((float)(b.e.offset - a.offset) / (a.slope - b.e.slope));
        #ifndef NDEBUG
        printf("Lines intersect at x = %lli.\n", res.x);
        #endif
        if (b.begin > res.x || res.x > b.end) {
            res.intersect = false;
            #ifndef NDEBUG
            printf("Point of intersection at %lli is not within segment bounds.\n", res.x);
            printf("Segment is (%lli, %lli).\n", b.begin, b.end);
            #endif
        }

        return res;
    }

    /*
    void print() {
        printf("Printing %i line(s).\n", (int)line_by_endpoint.size());
        for (map< lli, Line >::iterator it = line_by_endpoint.begin();
            it != line_by_endpoint.end();
            ++it) {
            printf("Line (%lli %llix) begins at ", it->second.offset, it->second.slope);
            if (it->first == -INF) {
                printf("-∞");
            }
            else {
                printf("%lli", it->first);
            }
            printf(".\n");
        }
    }
    */

    void clear() {
        line_by_endpoint.clear();
        endpoint_by_slope.clear();
    }
};
int N;
lli A[MAX_N], D[MAX_N], DP[MAX_N];

int main() {
    line_set s;

    scanf("%i", &N);

    DP[0] = A[0] = D[0] = 0;
    for (int i = 1; i <= N + 1; ++i) {
        scanf("%lli %lli", &A[i], &D[i]);
        DP[i] = max((lli)0, s.find(i));
        s.insert((Line){DP[i] + A[i] + i * D[i], -D[i]});
    }
    printf("%lli\n", DP[N + 1]);

    return 0;
}
