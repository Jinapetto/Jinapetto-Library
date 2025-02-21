bool shift(double start_temp,double end_temp,double end_time,double start_time,double scoredist,double now_time){
  long long INF = 1e18;
  double temp = start_temp + (end_temp - start_temp) * (now_time-start_time) / (end_time - start_time);  //線形でstart_tempからend_tempに変化する。
  double prob = exp(((double)scoredist)/temp); //scoredistが正のときは1負のときは1未満
  return (prob > (xor128()%INF)/(double)INF);
}
