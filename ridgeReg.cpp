/*Ridge regression: OLS with a penalty term on the l2-norm to prevent overfitting
cost function J = 0.5*||h-y||^2 + 0.5*lambda*theta^2
*/
#include <iostream>
#include <fstream>
#include <armadillo>

#include "ridgeRegSettings.cpp"

arma::mat train_normal (arma::mat X, arma::mat y);

/* By default, number of iterations will be 1500 and learning rate alpha will be 0.01*/
arma::mat train_batchGradDescent(arma::mat X, arma::mat y);

int main() {
  //initiallization
  arma::mat y;
  y.load(y_dat.c_str());
  arma::mat X_data;
  X_data.load(X_dat.c_str());
  //add X_0=1 to X
  arma::mat icept(X_data.n_rows,1);
  icept.ones();
  arma::mat X=join_horiz(icept, X_data);

  //Training parameters
  arma::mat theta = train_batchGradDescent(X,y);
  std::cout << theta << std::endl;

  //fit the data and output predictions
  if (newDat) {  //if newDat == "True"
    arma::mat newX;
    newX.load(newData.c_str());
    arma::mat h = newX*theta;
    std::ofstream ofs_h("linRegHypothesis.out");
    for (int i=0;i<newX.n_rows;i++) {
      ofs_h << h.row(i) << std::endl;
    }
  }  
}

arma::mat train_normal (arma::mat X, arma::mat y) {
  arma::mat theta(X.n_cols,1);
  arma::mat I(X.n_cols,X.n_cols);
  I.eye();
  theta = inv(trans(X)*X + lambda*I)*(trans(X)*y);
  return theta;
}

arma::mat train_batchGradDescent(arma::mat X, arma::mat y) {
  arma::mat theta(X.n_cols,1);
  theta.zeros();
  for (int k=0;k<numIter;k++) {
    theta = theta - (alpha/X.n_rows)*(trans(X)*(X*theta - y) + lambda*theta);
  }
  return theta;
}







