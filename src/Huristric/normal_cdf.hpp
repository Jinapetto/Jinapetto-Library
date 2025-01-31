double normal_cdf(double mean, double std_dev, double x){
    return 0.5 * (1.0 + erf((x - mean) / (std_dev * sqrt(2.0))));
}
