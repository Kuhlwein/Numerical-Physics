#include <armadillo>
using namespace std;
using namespace arma;

vec reflection(vec highest, vec centroid) {return 2*centroid-highest;}
vec expansion(vec highest, vec centroid) {return 3*centroid-2*highest;}
vec contraction(vec highest, vec centroid) {return 0.5*centroid+0.5*highest;}

void reduction(mat &simplex, int lo) {
	for(int k=0; k<simplex.n_cols;k++) if(k!=lo) simplex.col(k)=0.5*(simplex.col(k)+simplex.col(lo));
}

double size(mat simplex) {
	double s=0;
	for(int k=1; k<simplex.n_cols;k++) {
		double dist=norm(simplex.col(k)-simplex.col(0));
		s=(dist>s) ? dist : s;
	}
	return s;
}

void update(mat simplex, vec f_val, int &hi, int &lo, vec &centroid) {
	hi=0; lo=0; int d=simplex.n_rows;
	double highest=f_val(0), lowest=f_val(0);
	for(int i=1; i<d+1; i++) {
		if(f_val(i)>highest) {highest=f_val(i);hi=i;}
		if(f_val(i)<lowest) {lowest=f_val(i);lo=i;}
	}
	for(int i=0; i<d; i++) centroid(i)=(sum(simplex.row(i))-simplex(i,hi))/d;
}

void initiate(function<double(vec)> f, mat simplex, vec &f_val, int &hi, int &lo, vec &centroid) {
	for(int i=0;i<simplex.n_cols;i++) f_val(i)=f(simplex.col(i));
	update(simplex,f_val,hi,lo,centroid);
}

void downhill_simplex(function<double(vec)> f, mat &simplex, double goal) {
	int hi, lo, d=simplex.n_rows;
	vec centroid(d), f_val(d+1), p1(d), p2(d);
	initiate(f,simplex,f_val,hi,lo,centroid);
	while(size(simplex)>goal) {
		update(simplex,f_val,hi,lo,centroid);
		p1 = reflection(simplex.col(hi),centroid); double f_re=f(p1);
		if(f_re<f_val(lo)) {
			p2=expansion(simplex.col(hi),centroid); double f_ex=f(p2);
			simplex.col(hi)=(f_ex<f_re)?p2:p1;
			f_val(hi)=(f_ex<f_re)?f_ex:f_re;
		} else {
			if (f_re<f_val(hi)) {simplex.col(hi)=p1; f_val(hi)=f_re;}
			else {
				p1 = contraction(simplex.col(hi),centroid); double f_co=f(p1);
				if(f_co>f_val(hi)) {simplex.col(hi)=p1; f_val(hi)=f_co;}
				else {reduction(simplex,lo);initiate(f,simplex,f_val,hi,lo,centroid);}
			}
		}
	}
}
