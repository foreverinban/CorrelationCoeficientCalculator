#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
#include <vector>
#include <fstream>

using namespace std;

struct Coordinate{
  double x;
  double y;
};

vector<Coordinate> readfromfile(const string& fileName){
  ifstream datafile(fileName);
  vector<Coordinate> coord;
  Coordinate c;

  if (!datafile){
    cerr << "Cannot open file: " << fileName << endl;
    return coord;
  }

  while (datafile >> c.x >> c.y){
    coord.push_back(c);
  }

  return coord;
}

size_t menu(){
  size_t choice;
  cout << "1 -- Enter the data manually" << endl;
  cout << "2 -- Read the data from file" << endl;
  cout << "Enter the option (1/2): ";
  cin >> choice;
  while (choice != 1 and choice != 2){
    cout << "Incorrect option try again (1-2): ";
    cin >> choice;
  }
  return choice;
}

int main(int argc, char** argv)
{
    size_t choice = menu();
    size_t n = 0;
    double x;
    double y;
    double sx  = 0.0;
    double sy  = 0.0;
    double sxx = 0.0;
    double sxy = 0.0;
    double syy = 0.0;
    vector<double> cx;
    vector<double> cy;

    if (choice == 1){
      cout << "Enter the number of coordinate pairs: ";
      cin >> n;
      cout << "Enter " << n << " coordinate pairs (x y):" << endl;

      for(size_t i = 0; i < n; i++)
      {
        cin >> x >> y;
        cx.push_back(x);
        cy.push_back(y);
        sx  += x;
        sy  += y;
        sxx += x * x;
        sxy += x * y;
        syy += y * y;
      }
    } else {
      string fileName;
      cout << "Enter file path: ";
      cin >> fileName;
      vector<Coordinate> coord = readfromfile(fileName);
      if (coord.empty()){
        cerr << "No valid coordinate pairs found." << endl;
        return 1;
      }
      
      n = coord.size();
      for (const auto& c : coord){
        cx.push_back(x);
        cy.push_back(y);
        sx  += c.x;
        sy  += c.y;
        sxx += c.x * c.x;
        sxy += c.x * c.y;
        syy += c.y * c.y;
      }
    }
  
    
    double d = n * sxx - sx * sx;
    double a = (sy * sxx - sx * sxy) / d;
    double b = ( n * sxy - sx * sy ) / d;
    double meanx = sx / n;
    double meany = sy / n;
    double cov   = (sxy / n) - meanx * meany;
    double varx  = (sxx / n) - meanx * meanx;
    double vary  = (syy / n) - meany * meany;
    double sdevx = sqrt(varx);
    double sdevy = sqrt(vary);
    double r = cov / (sdevx * sdevy);
    double error = 0;
    double errorTemp = 0;
    double vectorsSize = cx.size();

    for(int i = 0; i < vectorsSize; i++){
      errorTemp = cy[i] - a - b * cx[i];
      error += errorTemp * errorTemp;
      errorTemp = 0;
    }
    
    cout << endl;
    cout << "  number of data points: " << n << endl << endl;
    cout << "  regression parameters: y = a + b * x" << endl;
    cout << "  a = " << a << endl;
    cout << "  b = " << b << endl << endl;
    cout << "  correlation r = " << r << endl << endl;
    cout << "  mean x = " << meanx << endl;
    cout << "  mean y = " << meany << endl << endl;
    cout << "  cov(x,y) = " << cov << endl;
    cout << "  var x = " << varx << endl;
    cout << "  var y = " << vary << endl << endl;
    cout << "  standard deviation x = " << sdevx << endl;
    cout << "  standard deviation y = " << sdevy << endl << endl;
    cout << "  error = " << error << endl << endl;
    return 0;
}

