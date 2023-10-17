#include <stdio.h>
#include <math.h>

typedef struct segment{
    float x1,y1,x2,y2;
}segment;

segment readSegment(){
    segment p;
    scanf("%f %f %f %f",&p.x1,&p.y1,&p.x2,&p.y2);
    return p;
}

int segments_intersect(segment s1, segment s2) {
    double dx1 = s1.x2 - s1.x1;
    double dy1 = s1.y2 - s1.y1;
    double dx2 = s2.x2 - s2.x1;
    double dy2 = s2.y2 - s2.y1;
    double delta = dx1 * dy2 - dx2 * dy1;

    // check if the segments are parallel or coincident
    if (delta == 0) {
        if ((s2.y1 - s1.y1) * dx1 - (s2.x1 - s1.x1) * dy1 == 0) {
            // segments are coincident
            return 1;
        } else {
            // segments are parallel and non-intersecting
            return 0;
        }
    }

    // compute the intersection point of the two lines
    double s = ((s2.x1 - s1.x1) * dy2 - (s2.y1 - s1.y1) * dx2) / delta;
    double t = ((s1.x1 - s2.x1) * dy1 - (s1.y1 - s2.y1) * dx1) / -delta;

    // check if the intersection point is on both segments
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        // segments intersect
        return 1;
    } else {
        // segments do not intersect
        return 0;
    }
}


int main(){
    segment s1= readSegment();
    segment s2=readSegment();
    printf("%d", segments_intersect(s1,s2));
    return 0;
}