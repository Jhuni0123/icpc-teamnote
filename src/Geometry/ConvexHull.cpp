int N,M,T,K,V;

ll ccw(ll x1 ,ll y1, ll x2, ll y2, ll x3, ll y3){
	ll ax = x2-x1; ll ay = y2-y1;
	ll bx = x3-x1; ll by = y3-y1;
	return (ax*by)-(bx*ay);
}


typedef struct Point{
	ll x,y,n;
} Point;

ll ccw(Point& a, Point& b, Point& c){
	return ccw(a.x,a.y,b.x,b.y,c.x,c.y);
}
bool cmp(const Point& a, const Point& b ){
	if( a.y == b.y ) return a.x > b.x;
	return a.y < b.y;
}

Point p[100500];

bool cmp_angle(const Point& a,const Point& b){
	if( ccw(0,0,a.x,a.y,b.x,b.y) == 0 ){
		return a.x*a.x+a.y*a.y < b.x*b.x+b.y*b.y;
	}
	return ccw(0,0,a.x,a.y,b.x,b.y) > 0;
}

int x[100500], y[100500];

int main(void)
{
	geti(N);
	repp(i,N) p[i].n = i;
	repp(i,N) scanf("%lld%lld",&p[i].x,&p[i].y);
	sort(p+1,p+N+1,cmp);
	for(int i=2;i<=N;i++){
		p[i].x -= p[1].x; p[i].y -= p[1].y;
	}
	
	p[1].x = p[1].y = 0;
	sort(p+1,p+N+1,cmp_angle);
	
	stack<Point> stk; stk.push(p[1]);
	for(int i=2;i<=N;i++){
		if( stk.size() <= 1 ){
			stk.push(p[i]); continue;
		}
		Point p3 = p[i];
		Point p2 = stk.top(); stk.pop();
		Point p1 = stk.top(); stk.pop();
		
		if( ccw(p1,p2,p3) > 0 ){
			stk.push(p1); stk.push(p2); stk.push(p3); continue;
		}else if( ccw(p1,p2,p3) <= 0 ){
			//p2 제거
			stk.push(p1); i--; continue;
		}
	}
	
	printf("%d",(int)stk.size());

}