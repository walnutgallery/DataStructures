double polynomial(int c, vector<double> poly){
double power=1;
double y=poly.at(1);

for(i=1;i<poly.size();i++){
	power=power*c;
	y+=y+poly[i]*power;
}
return y;
}

double Horner(int c, vector<double>poly){
double y=*poly.end();
for(i=1;i<poly.size();i++){
	y=y*c+*(poly.end()-i);
}
return y;
}


/// @brief Create test and run test
int main() {

  return 0;
}