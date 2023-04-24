#include "MojVektor.hpp"
#include <iostream>

int getItVal(const MojVektor& mVec, MojVektor::Iterator it){
  if(it < mVec.begin())
    return -1;
  else if(it >= mVec.end())
    return -2;
  else 
    return *it;
}

int main(int argc, char *argv[])
{
  MojVektor mVec{2,3,5,6,7,8};
  auto it = mVec.begin();
  //insert
  it = mVec.insert(mVec.begin(), 1);
  std::cout << getItVal(mVec, it) << " " << mVec << std::endl;

  it = mVec.insert(mVec.end(), 9);
  std::cout << getItVal(mVec, it) << " " << mVec << std::endl;

  it = mVec.insert(mVec.begin() + 3, 4);
  std::cout << getItVal(mVec, it) << " " << mVec << std::endl;

  //erase one
  mVec = {1,2,3,4,5,6,7,8};
  it = mVec.begin();

  it = mVec.erase(mVec.begin());
  std::cout << getItVal(mVec, it) << " " << mVec << std::endl;

  it = mVec.erase(mVec.end() - 1);
  std::cout << getItVal(mVec, it) << " " << mVec << std::endl;

  it = mVec.erase(mVec.begin() + 2);
  std::cout << getItVal(mVec, it) << " " << mVec << std::endl;

  //erase range
  mVec = {1,2,3,4,5,6,7,8,10,11};
  it = mVec.begin();

  it = mVec.erase(mVec.begin(), mVec.begin() + 3);
  std::cout << getItVal(mVec, it) << " " << mVec << std::endl;

  it = mVec.erase(mVec.end() - 3, mVec.end());
  std::cout << getItVal(mVec, it) << " " << mVec << std::endl;

  it = mVec.erase(mVec.begin() + 1, mVec.end() - 1);
  std::cout << getItVal(mVec, it) << " " << mVec << std::endl;

  it = mVec.erase(mVec.begin(), mVec.end());
  std::cout << getItVal(mVec, it) << " " << mVec << std::endl;

  return 0;
}
