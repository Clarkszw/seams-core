#include <bop.hpp>
#include <iostream>

namespace bg = boost::geometry;

// //SPHERICAL HARMONIC FUNCTIONS
// /********************************************/ /**
//  *  Spherical harmonics using boost
//  ***********************************************/
// std::vector<std::complex<double>>
// sph::spheriHarmo(int orderL, std::array<double, 2> radialCoord) {
//   // Iterate over the index of order
//   std::vector<int> v = {-3, -2, -1, 0, 1, 2, 3};
//   // For keeping track of the index of the output vector
//   int i(0);
//   std::vector<std::complex<double>> result;
//   for (auto n : v) {
//     auto theta = radialCoord[1];
//     auto phi = radialCoord[0];
//     result.resize(result.size() + 1);
//     // This is for l=3
//     std::complex<double> b =
//         boost::math::spherical_harmonic(orderL, n, theta, phi);
//     result[i] = b;
//     // Update the index
//     i++;
//   }
//   return result;
// }

/********************************************/ /**
 *  Spherical harmonics using boost (General)
 ***********************************************/
std::vector<std::complex<double>>
sph::spheriHarmo(int orderL, std::array<double, 2> radialCoord) {
  // For keeping track of the index of the output vector
  std::vector<std::complex<double>> result;
  std::complex<double> b; // Boost temp value
  int m;

  result.resize(2 * orderL + 1);

  for (int k = 0; k < 2 * orderL + 1; k++) {
    double theta = radialCoord[1];
    double phi = radialCoord[0];
    m = k - orderL;
    result[k] = boost::math::spherical_harmonic(orderL, m, theta, phi);
  }

  return result;
}

std::array<double, 2> sph::radialCoord(std::array<double, 3> cartCoord) {
  // The output
  std::array<double, 2> result;
  // Point Definitions
  bg::model::point<long double, 3, bg::cs::cartesian> cartesianPoint;
  bg::model::point<long double, 3, bg::cs::spherical<bg::radian>> azuPoint;
  // Set Value (TODO: Recurse this)
  bg::set<0>(cartesianPoint, cartCoord[0]);
  bg::set<1>(cartesianPoint, cartCoord[1]);
  bg::set<2>(cartesianPoint, cartCoord[2]);
  // Transform
  bg::transform(cartesianPoint, azuPoint);
  result[0] = bg::get<0>(azuPoint);
  result[1] = bg::get<1>(azuPoint);
  return result;
}

/********************************************/ /**
 *  Get Q3 using lookup tables
 ***********************************************/
std::vector<std::complex<double>>
sph::lookupTableQ3Vec(std::array<double, 2> angles) {
  // For keeping track of the index of the output vector
  std::vector<std::complex<double>> result;
  double theta = angles[1];
  double phi = angles[0];

  result.resize(7);

  for (int m = 0; m < 7; m++) {
    result[m] = sph::lookupTableQ3(m, angles);
  }

  return result;
}

/********************************************/ /**
 *  Lookup table for Q3
 ***********************************************/
std::complex<double> sph::lookupTableQ3(int m, std::array<double, 2> angles) {
  std::complex<double> result(0.0, 0.0);
  const double pi = std::acos(-1);
  const std::complex<double> i(0.0, 1.0);
  double constant;
  double theta = angles[1];
  double phi = angles[0];

  if (m == 0) {
    constant = 0.125 * std::sqrt(35 / pi);
    result = constant * std::exp(-3.0 * i * phi) * std::pow(sin(theta), 3.0);
    return result;
  } else if (m == 1) {
    constant = 0.25 * std::sqrt(105 / (2 * pi));
    result = constant * std::exp(-2.0 * i * phi) * std::pow(sin(theta), 2.0) *
             cos(theta);
    return result;
  } else if (m == 2) {
    constant = 0.125 * std::sqrt(21 / pi);
    result = constant * std::exp(-1.0 * i * phi) * sin(theta) *
             (5.0 * std::pow(cos(theta), 2.0) - 1);
    return result;
  } else if (m == 3) {
    constant = 0.25 * std::sqrt(7 / pi);
    result = constant * (5.0 * std::pow(cos(theta), 3.0) - 3.0 * cos(theta));
    return result;
  } else if (m == 4) {
    constant = -0.125 * std::sqrt(21 / pi);
    result = constant * std::exp(i * phi) * sin(theta) *
             (5.0 * std::pow(cos(theta), 2.0) - 1);
    return result;
  } else if (m == 5) {
    constant = 0.25 * std::sqrt(105 / (2 * pi));
    result = constant * std::exp(2.0 * i * phi) * std::pow(sin(theta), 2.0) *
             cos(theta);
    return result;
  } else if (m == 6) {
    constant = -0.125 * std::sqrt(35 / pi);
    result = constant * std::exp(3.0 * i * phi) * std::pow(sin(theta), 3.0);
    return result;
  }

  return result;
}

/********************************************/ /**
 *  Get Q6 using lookup tables
 ***********************************************/
std::vector<std::complex<double>>
sph::lookupTableQ6Vec(std::array<double, 2> angles) {
  // For keeping track of the index of the output vector
  std::vector<std::complex<double>> result;
  double theta = angles[1];
  double phi = angles[0];

  result.resize(13);

  for (int m = 0; m < 13; m++) {
    result[m] = sph::lookupTableQ6(m, angles);
  }

  return result;
}

/********************************************/ /**
 *  Lookup table for Q6
 ***********************************************/
std::complex<double> sph::lookupTableQ6(int m, std::array<double, 2> angles) {
  std::complex<double> result(0.0, 0.0);
  const double pi = std::acos(-1);
  const std::complex<double> i(0.0, 1.0);
  double constant;
  double theta = angles[1];
  double phi = angles[0];

  if (m == 0) {
    constant = 0.015625 * std::sqrt(3003 / pi);
    result = constant * std::exp(-6.0 * i * phi) * std::pow(sin(theta), 6.0);
    return result;
  } else if (m == 1) {
    constant = 0.09375 * std::sqrt(1001 / pi);
    result = constant * std::exp(-5.0 * i * phi) * std::pow(sin(theta), 5.0) *
             cos(theta);
    return result;
  } else if (m == 2) {
    constant = 0.09375 * std::sqrt(91 / (2 * pi));
    result = constant * std::exp(-4.0 * i * phi) * std::pow(sin(theta), 4.0) *
             (11.0 * std::pow(cos(theta), 2.0) - 1);
    return result;
  } else if (m == 3) {
    constant = 0.03125 * std::sqrt(1365 / pi);
    result = constant * std::exp(-3.0 * i * phi) * std::pow(sin(theta), 3.0) *
             (11.0 * std::pow(cos(theta), 3.0) - 3.0 * cos(theta));
    return result;
  } else if (m == 4) {
    constant = 0.015625 * std::sqrt(1365 / pi);
    result = constant * std::exp(-2.0 * i * phi) * std::pow(sin(theta), 2.0) *
             (33.0 * std::pow(cos(theta), 4.0) -
              18.0 * std::pow(cos(theta), 2.0) + 1.0);
    return result;
  } else if (m == 5) {
    constant = 0.0625 * std::sqrt(273 / (2 * pi));
    result = constant * std::exp(-1.0 * i * phi) * sin(theta) *
             (33.0 * std::pow(cos(theta), 5.0) -
              30.0 * std::pow(cos(theta), 3.0) + 5.0 * cos(theta));
    return result;
  } else if (m == 6) {
    constant = 0.03125 * std::sqrt(13 / pi);
    result = constant * (231.0 * std::pow(cos(theta), 6.0) -
                         315.0 * std::pow(cos(theta), 4.0) +
                         105.0 * std::pow(cos(theta), 2.0) - 5.0);
    return result;
  } else if (m == 7) {
    constant = -0.0625 * std::sqrt(273 / (2 * pi));
    result = constant * std::exp(i * phi) * sin(theta) *
             (33.0 * std::pow(cos(theta), 5.0) -
              30.0 * std::pow(cos(theta), 3.0) + 5.0 * cos(theta));
    return result;
  } else if (m == 8) {
    constant = 0.015625 * std::sqrt(1365 / pi);
    result = constant * std::exp(2.0 * i * phi) * std::pow(sin(theta), 2.0) *
             (33.0 * std::pow(cos(theta), 4.0) -
              18.0 * std::pow(cos(theta), 2.0) + 1.0);
    return result;
  } else if (m == 9) {
    constant = -0.03125 * std::sqrt(1365 / pi);
    result = constant * std::exp(3.0 * i * phi) * std::pow(sin(theta), 3.0) *
             (11.0 * std::pow(cos(theta), 3.0) - 3.0 * cos(theta));
    return result;
  } else if (m == 10) {
    constant = 0.09375 * std::sqrt(91 / (2 * pi));
    result = constant * std::exp(4.0 * i * phi) * std::pow(sin(theta), 4.0) *
             (11.0 * std::pow(cos(theta), 2.0) - 1);
    return result;
  } else if (m == 11) {
    constant = -0.09375 * std::sqrt(1001 / pi);
    result = constant * std::exp(5.0 * i * phi) * std::pow(sin(theta), 5.0) *
             cos(theta);
    return result;
  } else if (m == 12) {
    constant = 0.015625 * std::sqrt(3003 / pi);
    result = constant * std::exp(6.0 * i * phi) * std::pow(sin(theta), 6.0);
    return result;
  }

  return result;
}

/********************************************/ /**
 *  Function for getting the bond order correlations c_{ij}
 according to the CHILL algorithm
 ***********************************************/
molSys::PointCloud<molSys::Point<double>, double>
chill::getCorrel(molSys::PointCloud<molSys::Point<double>, double> *yCloud,
                 bool isSlice) {
  //
  int l = 3; // Don't hard-code this; change later
  int jatom; // Index of nearest neighbour
  std::array<double, 3> delta;
  std::array<double, 2> angles;
  chill::QlmAtom QlmTotal; // Qlm for each iatom
  std::vector<std::complex<double>>
      yl; // temp q_lm for each pair of iatom and jatom
  std::complex<double> dot_product = {0, 0};
  std::complex<double> qI = {0, 0};
  std::complex<double> qJ = {0, 0};
  std::complex<double> Inorm = {0, 0};
  std::complex<double> Jnorm = {0, 0};
  std::complex<double> complexDenominator = {0, 0};
  std::complex<double> complexCij = {0, 0};
  molSys::Result temp_cij; // Holds the c_ij value
  double cij_real;
  int nnumNeighbours;

  QlmTotal.ptq.resize(yCloud->nop);

  for (int iatom = 0; iatom < yCloud->nop; iatom++) {
    // if(yCloud->pts[iatom].type!=typeO){continue;}

    nnumNeighbours = yCloud->pts[iatom].neighList.size();
    // Now loop over the first four neighbours
    for (int j = 0; j < nnumNeighbours; j++) {
      jatom = yCloud->pts[iatom].neighList[j];

      delta = gen::relDist(yCloud, iatom, jatom);

      // delta[0] = yCloud->pts[iatom].x - yCloud->pts[jatom].x;
      //  		delta[1] = yCloud->pts[iatom].y - yCloud->pts[jatom].y;
      //  		delta[2] = yCloud->pts[iatom].z - yCloud->pts[jatom].z;
      // angles = sph::radialCoord(delta);
      double r = std::sqrt(std::pow(delta[0], 2.0) + std::pow(delta[1], 2.0) +
                           std::pow(delta[2], 2.0));
      angles[1] = acos(delta[2] / r);        // theta
      angles[0] = atan2(delta[0], delta[1]); // phi

      // Now add over all nearest neighbours
      if (j == 0) {
        // QlmTotal.ptq[iatom].ylm = sph::spheriHarmo(3, angles);
        QlmTotal.ptq[iatom].ylm = sph::lookupTableQ3Vec(angles);
        continue;
      }
      // Not for the first jatom
      yl = sph::spheriHarmo(3, angles);
      for (int m = 0; m < 2 * l + 1; m++) {
        // QlmTotal.ptq[iatom].ylm[m] += yl[m];
        QlmTotal.ptq[iatom].ylm[m] += sph::lookupTableQ3(m, angles);
      }
    } // End of loop over 4 nearest neighbours

    // Divide by 4
    QlmTotal.ptq[iatom].ylm =
        avgVector(QlmTotal.ptq[iatom].ylm, l, nnumNeighbours);
  } // End of looping over all iatom

  // ------------------------------------------------
  // Now that you have all qlm for the particles,
  // find c_ij
  for (int iatom = 0; iatom < yCloud->nop; iatom++) {
    // if(yCloud->pts[iatom].type!=typeO){continue;}
    // // if this is a slice and the particle is not in the slice
    // // then skip
    if (isSlice) {
      if (yCloud->pts[iatom].inSlice == false) {
        continue;
      }
    }
    // Check if there are 4 neighbours or not
    // if (yCloud->pts[iatom].neighList.size()<4){nnumNeighbours=yCloud->pts[iatom].neighList.size();}
    // else{nnumNeighbours=4;}
    nnumNeighbours = yCloud->pts[iatom].neighList.size();
    yCloud->pts[iatom].c_ij.reserve(nnumNeighbours);
    // loop over the 4 nearest neighbours
    for (int j = 0; j < nnumNeighbours; j++) {
      // Init to zero
      dot_product = {0, 0};
      Inorm = {0, 0};
      Jnorm = {0, 0};
      // Get index of the nearest neighbour
      jatom = yCloud->pts[iatom].neighList[j];
      for (int m = 0; m < 2 * l + 1; m++) {
        qI = QlmTotal.ptq[iatom].ylm[m];
        qJ = QlmTotal.ptq[jatom].ylm[m];
        dot_product = dot_product + (qI * std::conj(qJ)); // unnormalized
        Inorm = Inorm + (qI * std::conj(qI));
        Jnorm = Jnorm + (qJ * std::conj(qJ));
      } // end loop over m components
      // Get the denominator
      complexDenominator = std::sqrt(Inorm * Jnorm);
      complexCij = dot_product / complexDenominator;
      // Update c_ij and type
      cij_real = complexCij.real();
      temp_cij.c_value = cij_real;
      if (cij_real < -0.8) {
        temp_cij.classifier = molSys::staggered;
      } else if (cij_real > -0.2 && cij_real < -0.05) {
        temp_cij.classifier = molSys::eclipsed;
      } else {
        temp_cij.classifier = molSys::out_of_range;
      }
      yCloud->pts[iatom].c_ij.push_back(temp_cij);
    } // end loop over nearest neighbours
  }

  return *yCloud;
}

/********************************************/ /**
 *  Function that classifies each ice type according to 
 the CHILL algorithm
 ***********************************************/
molSys::PointCloud<molSys::Point<double>, double>
chill::getIceType(molSys::PointCloud<molSys::Point<double>, double> *yCloud,
                  bool isSlice, std::string outputFileName) {
  int ih, ic, water, interIce, unknown, total; // No. of particles of each type
  ih = ic = water = unknown = interIce = total = 0;
  int num_staggrd, num_eclipsd, na;
  molSys::bond_type bondType;

  for (int iatom = 0; iatom < yCloud->nop; iatom++) {
    // if(yCloud->pts[iatom].type!=typeO){continue;}
    // if this is a slice and the particle is not in the slice
    // then skip
    if (isSlice) {
      if (yCloud->pts[iatom].inSlice == false) {
        continue;
      }
    }
    total++; // Update the total number of atoms considered. Change this to a check for slices
    num_staggrd = num_eclipsd = na =
        0; // init to zero before loop through neighbours
    // Loop through the bond cij and get the number of staggered, eclipsed bonds
    for (int j = 0; j < 4; j++) {
      bondType = yCloud->pts[iatom].c_ij[j].classifier;
      if (bondType == molSys::eclipsed) {
        num_eclipsd++;
      } else if (bondType == molSys::staggered) {
        num_staggrd++;
      } else {
        na++;
      }
    } // End of loop through neighbours

    // Add more tests later
    yCloud->pts[iatom].iceType = molSys::unclassified; // default
    // Cubic ice
    // if (num_eclipsd==0 && num_staggrd==4){
    // 	yCloud->pts[iatom].iceType = molSys::cubic;
    // 	ic++;
    // }
    if (num_staggrd >= 4) {
      yCloud->pts[iatom].iceType = molSys::cubic;
      ic++;
    }
    // Hexagonal
    else if (num_eclipsd == 1 && num_staggrd == 3) {
      yCloud->pts[iatom].iceType = molSys::hexagonal;
      ih++;
    }
    // Interfacial
    else if (isInterfacial(yCloud, iatom, num_staggrd, num_eclipsd)) {
      yCloud->pts[iatom].iceType = molSys::interfacial;
      interIce++;
    } else {
      yCloud->pts[iatom].iceType = molSys::water;
      water++;
    }

  } // End of loop through every iatom

  // water = total - ic -ih;

  // Test; do pretty printing instead
  // std::cout<<"For frame " << yCloud->currentFrame <<" , the number of ic= "<<ic<<" , ih= "<<ih<<" interfacial ice= "<<interIce<<" and water= "<<water<<"\n";
  // std::cout<<"For frame " << yCloud->currentFrame <<" , ic= "<<(double)ic/(double)total * 100
  // <<"% , ih= "<<(double)ih/(double)total * 100<<"% interfacial ice= "<<(double)interIce/(double)total * 100<<"% and water= "<<(double)water/(double)total * 100<<"% \n";
  // std::cout<<"\n";

  // Print to file
  std::ofstream outputFile;
  outputFile.open(outputFileName, std::ios_base::app);
  outputFile << yCloud->currentFrame << " " << ic << " " << ih << " "
             << interIce << " " << water << " " << total << "\n";
  outputFile.close();

  return *yCloud;
}

/********************************************/ /**
 *  Function for getting the bond order correlations c_{ij}
 using the CHILL+ algorithm
 ***********************************************/
molSys::PointCloud<molSys::Point<double>, double>
chill::getCorrelPlus(molSys::PointCloud<molSys::Point<double>, double> *yCloud,
                     bool isSlice) {
  //
  int l = 3; // Don't hard-code this; change later
  int jatom; // Index of nearest neighbour
  std::array<double, 3> delta;
  std::array<double, 2> angles;
  chill::QlmAtom QlmTotal; // Qlm for each iatom
  std::vector<std::complex<double>>
      yl; // temp q_lm for each pair of iatom and jatom
  std::complex<double> dot_product = {0, 0};
  std::complex<double> qI = {0, 0};
  std::complex<double> qJ = {0, 0};
  std::complex<double> Inorm = {0, 0};
  std::complex<double> Jnorm = {0, 0};
  std::complex<double> complexDenominator = {0, 0};
  std::complex<double> complexCij = {0, 0};
  molSys::Result temp_cij; // Holds the c_ij value
  double cij_real;
  int nnumNeighbours;

  QlmTotal.ptq.resize(yCloud->nop);

  for (int iatom = 0; iatom < yCloud->nop; iatom++) {

    // if(yCloud->pts[iatom].type!=typeO){continue;}
    // Check if there are 4 neighbours or not
    // if (yCloud->pts[iatom].neighList.size()<4){nnumNeighbours=yCloud->pts[iatom].neighList.size();}
    // else{nnumNeighbours=4;
    // }
    nnumNeighbours = yCloud->pts[iatom].neighList.size();
    // Now loop over the first four neighbours
    for (int j = 0; j < nnumNeighbours; j++) {
      jatom = yCloud->pts[iatom].neighList[j];

      delta = gen::relDist(yCloud, iatom, jatom);
      // delta[0] = yCloud->pts[iatom].x - yCloud->pts[jatom].x;
      //  		delta[1] = yCloud->pts[iatom].y - yCloud->pts[jatom].y;
      //  		delta[2] = yCloud->pts[iatom].z - yCloud->pts[jatom].z;
      // angles = sph::radialCoord(delta);
      double r = std::sqrt(std::pow(delta[0], 2.0) + std::pow(delta[1], 2.0) +
                           std::pow(delta[2], 2.0));
      angles[1] = acos(delta[2] / r);        // theta
      angles[0] = atan2(delta[0], delta[1]); // phi

      // Now add over all nearest neighbours
      if (j == 0) {
        QlmTotal.ptq[iatom].ylm = sph::spheriHarmo(3, angles);
        // QlmTotal.ptq[iatom].ylm = sph::lookupTableQ3Vec(angles);
        continue;
      }
      // Not for the first jatom
      yl = sph::spheriHarmo(3, angles);
      for (int m = 0; m < 2 * l + 1; m++) {
        QlmTotal.ptq[iatom].ylm[m] += yl[m];
        // QlmTotal.ptq[iatom].ylm[m] += sph::lookupTableQ3(m, angles);
      }
    } // End of loop over 4 nearest neighbours

    // Divide by 4
    QlmTotal.ptq[iatom].ylm =
        avgVector(QlmTotal.ptq[iatom].ylm, l, nnumNeighbours);
  } // End of looping over all iatom

  // ------------------------------------------------
  // Now that you have all qlm for the particles,
  // find c_ij
  for (int iatom = 0; iatom < yCloud->nop; iatom++) {
    // if(yCloud->pts[iatom].type!=typeO){continue;}
    // if this is a slice and the particle is not in the slice
    // then skip
    if (isSlice) {
      if (yCloud->pts[iatom].inSlice == false) {
        continue;
      }
    }
    // Check if there are 4 neighbours or not
    // if (yCloud->pts[iatom].neighList.size()<4){nnumNeighbours=yCloud->pts[iatom].neighList.size();}
    // else{nnumNeighbours=4;}
    nnumNeighbours = yCloud->pts[iatom].neighList.size();
    yCloud->pts[iatom].c_ij.reserve(nnumNeighbours);
    // loop over the 4 nearest neighbours
    for (int j = 0; j < nnumNeighbours; j++) {
      // Init to zero
      dot_product = {0, 0};
      Inorm = {0, 0};
      Jnorm = {0, 0};
      // Get index of the nearest neighbour
      jatom = yCloud->pts[iatom].neighList[j];
      for (int m = 0; m < 2 * l + 1; m++) {
        qI = QlmTotal.ptq[iatom].ylm[m];
        qJ = QlmTotal.ptq[jatom].ylm[m];
        dot_product = dot_product + (qI * std::conj(qJ)); // unnormalized
        Inorm = Inorm + (qI * std::conj(qI));
        Jnorm = Jnorm + (qJ * std::conj(qJ));
      } // end loop over m components
      // Get the denominator
      complexDenominator = std::sqrt(Inorm * Jnorm);
      complexCij = dot_product / complexDenominator;
      // Update c_ij and type
      cij_real = complexCij.real();
      temp_cij.c_value = cij_real;
      if (cij_real <= -0.8) {
        temp_cij.classifier = molSys::staggered;
      } else if (cij_real >= -0.35 && cij_real <= 0.25) {
        temp_cij.classifier = molSys::eclipsed;
      } else {
        temp_cij.classifier = molSys::out_of_range;
      }
      yCloud->pts[iatom].c_ij.push_back(temp_cij);
    } // end loop over nearest neighbours
  }

  // ------------------------------------------------

  return *yCloud;
}

/********************************************/ /**
 *  Function that classifies each ice type according to the CHILL+
 algorithm
 ***********************************************/
molSys::PointCloud<molSys::Point<double>, double>
chill::getIceTypePlus(molSys::PointCloud<molSys::Point<double>, double> *yCloud,
                      bool isSlice, std::string outputFileName) {
  int ih, ic, interIce, water, unknown, clath, interClath,
      total; // No. of particles of each type
  ih = ic = water = unknown = interIce = total = 0;
  clath = interClath = 0;
  int num_staggrd, num_eclipsd, na;
  molSys::bond_type bondType;
  int nnumNeighbours; // number of nearest neighbours

  for (int iatom = 0; iatom < yCloud->nop; iatom++) {
    // if(yCloud->pts[iatom].type!=typeO){continue;}
    // if this is a slice and the particle is not in the slice
    // then skip
    if (isSlice) {
      if (yCloud->pts[iatom].inSlice == false) {
        continue;
      }
    }
    total++; // Update the total number of atoms considered. Change this to a check for slices
    nnumNeighbours =
        yCloud->pts[iatom].neighList.size(); // number of nearest neighbours
    num_staggrd = num_eclipsd = na =
        0; // init to zero before loop through neighbours
    // Loop through the bond cij and get the number of staggered, eclipsed bonds
    for (int j = 0; j < nnumNeighbours; j++) {
      bondType = yCloud->pts[iatom].c_ij[j].classifier;
      if (bondType == molSys::eclipsed) {
        num_eclipsd++;
      } else if (bondType == molSys::staggered) {
        num_staggrd++;
      } else {
        na++;
      }
    } // End of loop through neighbours

    // Add more tests later
    yCloud->pts[iatom].iceType = molSys::unclassified; // default
    if (nnumNeighbours == 4) {
      // Cubic ice
      if (num_eclipsd == 0 && num_staggrd == 4) {
        yCloud->pts[iatom].iceType = molSys::cubic;
        ic++;
      }
      // Hexagonal
      else if (num_eclipsd == 1 && num_staggrd == 3) {
        yCloud->pts[iatom].iceType = molSys::hexagonal;
        ih++;
      }
      // Interfacial
      else if (isInterfacial(yCloud, iatom, num_staggrd, num_eclipsd)) {
        yCloud->pts[iatom].iceType = molSys::interfacial;
        interIce++;
      }
      // Clathrate
      else if (num_eclipsd == 4 && num_staggrd == 0) {
        yCloud->pts[iatom].iceType = molSys::clathrate;
        clath++;
      }
      // Interfacial clathrate
      else if (num_eclipsd == 3) {
        yCloud->pts[iatom].iceType = molSys::interClathrate;
        interClath++;
      }
      // Water
      else {
        yCloud->pts[iatom].iceType = molSys::water;
        water++;
      }
    } else {
      yCloud->pts[iatom].iceType = molSys::water;
      water++;
    }

  } // End of loop through every iatom

  // water = total - ic -ih;

  // Test; do pretty printing instead
  // std::cout<<"For frame " << yCloud->currentFrame <<" , the number of ic= "<<ic<<" , ih= "<<ih<<" interfacial ice= "
  // <<interIce<<" , clathrate= "<<clath<<" , interfacial clathrate= "<<interClath<<" and water= "<<water<<" and the total is "<<total<<"\n";
  // std::cout<<"For frame " << yCloud->currentFrame <<" , ic= "<<(double)ic/(double)total * 100
  // <<"% , ih= "<<(double)ih/(double)total * 100<<"% interfacial ice= "<<(double)interIce/(double)total * 100<<"% and water= "<<(double)water/(double)total * 100<<"% \n";
  // std::cout<<"\n";
  // Print to file
  std::ofstream outputFile;
  outputFile.open(outputFileName, std::ios_base::app);
  outputFile << yCloud->currentFrame << " " << ic << " " << ih << " "
             << interIce << " " << clath << " " << interClath << " " << water
             << " " << total << "\n";
  outputFile.close();

  return *yCloud;
}

/********************************************/ /**
 *  Function for getting the averaged q6 paramter, 
 returning the values as a vector. TODO: SLICE!
 ***********************************************/
std::vector<double>
chill::getq6(molSys::PointCloud<molSys::Point<double>, double> *yCloud,
             bool isSlice) {
  //
  int l = 6; // We're using q6 here
  int jatom; // Index of nearest neighbour
  std::array<double, 3> delta;
  std::array<double, 2> angles;
  chill::QlmAtom QlmTotal; // Qlm for each iatom
  std::vector<std::complex<double>>
      yl; // temp q_lm for each pair of iatom and jatom
  std::complex<double> dot_product = {0, 0};
  std::complex<double> qI = {0, 0};
  std::complex<double> qJ = {0, 0};
  std::complex<double> Inorm = {0, 0};
  std::complex<double> Jnorm = {0, 0};
  std::complex<double> complexDenominator = {0, 0};
  std::complex<double> complexCij = {0, 0};
  double cij_real;
  int nnumNeighbours;
  std::vector<double> resultQ; // Vector with averaged q values
  double q_value = 0.0;        // Averaged q value per neighbour pair

  QlmTotal.ptq.resize(yCloud->nop);
  resultQ.resize(yCloud->nop);

  for (int iatom = 0; iatom < yCloud->nop; iatom++) {

    // if(yCloud->pts[iatom].type!=typeO){continue;}

    nnumNeighbours = yCloud->pts[iatom].neighList.size();
    // Now loop over the first four neighbours
    for (int j = 0; j < nnumNeighbours; j++) {
      jatom = yCloud->pts[iatom].neighList[j];
      // Get the relative distances
      delta = gen::relDist(yCloud, iatom, jatom);

      // angles = sph::radialCoord(delta);
      double r = std::sqrt(std::pow(delta[0], 2.0) + std::pow(delta[1], 2.0) +
                           std::pow(delta[2], 2.0));
      angles[1] = acos(delta[2] / r);        // theta
      angles[0] = atan2(delta[0], delta[1]); // phi

      // Now add over all nearest neighbours
      if (j == 0) {
        // QlmTotal.ptq[iatom].ylm = sph::spheriHarmo(l, angles);
        QlmTotal.ptq[iatom].ylm = sph::lookupTableQ6Vec(angles);
        continue;
      }
      // Not for the first jatom
      // yl = sph::spheriHarmo(l, angles);
      for (int m = 0; m < 2 * l + 1; m++) {
        // QlmTotal.ptq[iatom].ylm[m] += yl[m];
        QlmTotal.ptq[iatom].ylm[m] += sph::lookupTableQ6(m, angles);
      }
    } // End of loop over 4 nearest neighbours

    // Divide by 4
    QlmTotal.ptq[iatom].ylm =
        avgVector(QlmTotal.ptq[iatom].ylm, l, nnumNeighbours);
  } // End of looping over all iatom

  // ------------------------------------------------
  // Now that you have all qlm for the particles,
  // find c_ij
  for (int iatom = 0; iatom < yCloud->nop; iatom++) {
    // if(yCloud->pts[iatom].type!=typeO){continue;}
    // if this is a slice and the particle is not in the slice
    // then skip TODO: UNCOMMENT
    // if(isSlice){
    // 	if(yCloud->pts[iatom].inSlice==false){continue;}
    // }

    nnumNeighbours = yCloud->pts[iatom].neighList.size();
    q_value = 0.0; // initialize to zero
    // yCloud->pts[iatom].c_ij.reserve(nnumNeighbours);
    // loop over the 4 nearest neighbours
    for (int j = 0; j < nnumNeighbours; j++) {
      // Init to zero
      dot_product = {0, 0};
      Inorm = {0, 0};
      Jnorm = {0, 0};
      // Get index of the nearest neighbour
      jatom = yCloud->pts[iatom].neighList[j];
      for (int m = 0; m < 2 * l + 1; m++) {
        qI = QlmTotal.ptq[iatom].ylm[m];
        qJ = QlmTotal.ptq[jatom].ylm[m];
        dot_product = dot_product + (qI * std::conj(qJ)); // unnormalized
        Inorm = Inorm + (qI * std::conj(qI));
        Jnorm = Jnorm + (qJ * std::conj(qJ));
      } // end loop over m components
      // Get the denominator
      complexDenominator = std::sqrt(Inorm * Jnorm);
      complexCij = dot_product / complexDenominator;
      // Update c_ij and type
      cij_real = complexCij.real();

      q_value += cij_real;

    } // end loop over nearest neighbours

    // Average q_value over all nearest neighbours
    q_value /= (double)nnumNeighbours;

    resultQ[iatom] = q_value; // Update the vector of averaged q6
  }

  // ------------------------------------------------

  return resultQ;
}

/********************************************/ /**
 *  Reclassifies atoms which may have been misclassified
 as water using the averaged q6 and q3 parameters
 Call this after both averaged q6 and c_ij have been calculated
 https://pubs.rsc.org/en/content/articlehtml/2011/cp/c1cp22167a
 ***********************************************/
molSys::PointCloud<molSys::Point<double>, double> chill::reclassifyWater(
    molSys::PointCloud<molSys::Point<double>, double> *yCloud,
    std::vector<double> *q6) {
  // If averaged q6 > 0.5, then consider it to be ice
  // If averaged q3 < -0.75 then it is ih or ic. If q3 < -0.85 then it is cubic, otherwise it is hexagonal
  double avgQ3 = 0.0;
  int nnumNeighbours;

  for (int iatom = 0; iatom < yCloud->nop; iatom++) {
    // Check if it has been classified as water
    if (yCloud->pts[iatom].iceType == molSys::water) {
      if ((*q6)[iatom] > 0.5) {
        avgQ3 = 0.0; // init to zero
        // Loop through all c_ij
        nnumNeighbours = yCloud->pts[iatom].c_ij.size();
        for (int j = 0; j < nnumNeighbours; j++) {
          avgQ3 += yCloud->pts[iatom].c_ij[j].c_value;
        }
        avgQ3 /= (double)nnumNeighbours;

        // If averaged q3 < -0.75, then reclassify
        if (avgQ3 <= -0.75) {
          if (avgQ3 < -0.85) {
            yCloud->pts[iatom].iceType = molSys::cubic;
          } else {
            yCloud->pts[iatom].iceType = molSys::hexagonal;
          }
        } // end of reclassification
      }   // check for solid atom!
    }     // end of check for water
  }       // End loop through every iatom

  return *yCloud;
}

/********************************************/ /**
 *  Gets a PointCloud struct of all the solid particles for
 a given frame 
 ***********************************************/
molSys::PointCloud<molSys::Point<double>, double> chill::getIceCloud(
    molSys::PointCloud<molSys::Point<double>, double> *yCloud,
    molSys::PointCloud<molSys::Point<double>, double> *iceCloud) {

  int nIce = 0; // No. of ice particles
  // Update box info
  iceCloud->box = yCloud->box;

  for (int iatom = 0; iatom < yCloud->nop; iatom++) {
    if (yCloud->pts[iatom].iceType == molSys::water) {
      continue;
    } else {
      nIce++;
      iceCloud->pts.push_back(yCloud->pts[iatom]);
    }
  } // End of loop through all the atoms in yCloud

  iceCloud->nop = nIce;
  iceCloud->currentFrame = yCloud->currentFrame;
  iceCloud->boxLow = yCloud->boxLow;

  return *iceCloud;
}

/********************************************/ /**
 *  Finds the largest ice cluster for a given frame
 ***********************************************/
int chill::largestIceCluster(
    molSys::PointCloud<molSys::Point<double>, double> *iceCloud, double cutoff,
    bool printCluster, bool isSlice) {
  std::vector<int>
      clusterFlag; // This will contain flags for each solid atom. If 'flagged', move onto the next unflagged element
  std::vector<int>
      linkedListCluster; // This will contain the ID of the cluster it belongs to
  std::vector<int>
      clusterID; // This will contain the starting point of a cluster
  std::vector<int> nCluster; // No. of particles in each cluster
  int nLargestCluster = 0;   // No. of particles in the largest cluster
  int nnumNeighbours;        // Number of nearest neighbours
  int j;
  int noc = 0;     // no. of particles in a cluster
  double r_jk = 0; // Distance between j^th and k^th atom

  clusterFlag.resize(
      iceCloud
          ->nop); // Init cluster flag vector to 0. If added to a cluster, then skip
  linkedListCluster.reserve(iceCloud->nop);

  // Initialize the linked list
  for (int iatom = 0; iatom < iceCloud->nop; iatom++) {
    linkedListCluster[iatom] = iatom;
  }

  // -------------------------------------------------
  // Construct the linked list
  for (int i = 0; i < iceCloud->nop - 1; i++) {
    if (linkedListCluster[i] != i) {
      continue;
    } // i is already in a cluster
    j = i;
    do {
      for (int k = i + 1; k < iceCloud->nop; k++) {
        // If L[k] == k and r_jk < cutoff then
        if (linkedListCluster[k] == k) {
          r_jk = gen::periodicDist(iceCloud, j, k);
          if (r_jk <= cutoff) {
            iter_swap(linkedListCluster.begin() + j,
                      linkedListCluster.begin() + k);
          } // end of check that j&k are neighbours
        }   // check for L[k] and k
      }
      j = linkedListCluster[j];
    } while (j != i);

  } // Loop through N-1 atoms
  // -------------------------------------------------

  // Get the number of particles per cluster
  int jatom, iatom;

  for (int i = 0; i < iceCloud->nop; i++) {
    if (clusterFlag[i] == 1) {
      continue;
    } // The particle has already been tagged as part of a previous cluster
    // Start a new cluster
    clusterID.push_back(i);
    iatom = i;
    noc = 0;
    for (int j = 0; j < iceCloud->nop; j++) {
      jatom = linkedListCluster[iatom];
      clusterFlag[jatom] = 1;
      iatom = jatom;
      noc++;
      if (jatom == i) {
        break;
      }
    } // The maximum no. of particles in a cluster is N
    nCluster.push_back(noc);
  } // Loop through all solid particles

  auto largest = std::max_element(nCluster.begin(), nCluster.end());
  int indexOfCluster = std::distance(std::begin(nCluster), largest);
  nLargestCluster = nCluster[indexOfCluster];
  // -----------------------------------------------
  // If the user wants, print out the largest ice cluster to a lammpstrj

  if (printCluster) {
    // Header of traj file
    std::ofstream outputFile;
    // Create a new file in the output directory
    outputFile.open("largestCluster.lammpstrj", std::ios_base::app);
    outputFile << "ITEM: TIMESTEP\n";
    outputFile << iceCloud->currentFrame << "\n";
    outputFile << "ITEM: NUMBER OF ATOMS\n";
    outputFile << nLargestCluster << "\n";
    outputFile << "ITEM: BOX BOUNDS pp pp pp\n";
    for (int k = 0; k < iceCloud->boxLow.size(); k++) {
      outputFile << iceCloud->boxLow[k] << " "
                 << iceCloud->boxLow[k] + iceCloud->box[k] << "\n";
    } // end of printing box lengths
    outputFile << "ITEM: ATOMS id mol type x y z\n";

    iatom = clusterID[indexOfCluster];
    for (int i = 0; i < nLargestCluster; i++) {
      jatom = linkedListCluster[iatom]; // Get index of the atom to print
      iatom = jatom;
      outputFile << iceCloud->pts[jatom].atomID << " "
                 << iceCloud->pts[jatom].molID << " "
                 << iceCloud->pts[jatom].iceType << " "
                 << iceCloud->pts[jatom].x << " " << iceCloud->pts[jatom].y
                 << " " << iceCloud->pts[jatom].z << "\n";
    } // End of traversing through the largest ice cluster
  }

  // -------------------------------------------------

  return nLargestCluster;
}

/********************************************/ /**
 *  Prints out the iceType for a particular frame to a file
 ***********************************************/
int chill::printIceType(
    molSys::PointCloud<molSys::Point<double>, double> *yCloud, bool isSlice,
    std::string outputFileName) {
  int ih, ic, interIce, water, unknown, clath, interClath,
      total; // No. of particles of each type
  ih = ic = water = unknown = interIce = total = 0;
  clath = interClath = 0;

  for (int iatom = 0; iatom < yCloud->nop; iatom++) {
    // if(yCloud->pts[iatom].type != typeO){continue;}
    // check for slice
    if (isSlice) {
      if (yCloud->pts[iatom].inSlice == false) {
        continue;
      }
    }
    total++;
    if (yCloud->pts[iatom].iceType == molSys::cubic) {
      ic++;
    } else if (yCloud->pts[iatom].iceType == molSys::hexagonal) {
      ih++;
    } else if (yCloud->pts[iatom].iceType == molSys::water) {
      water++;
    } else if (yCloud->pts[iatom].iceType == molSys::interfacial) {
      interIce++;
    } else if (yCloud->pts[iatom].iceType == molSys::clathrate) {
      clath++;
    } else if (yCloud->pts[iatom].iceType == molSys::interClathrate) {
      interClath++;
    } else {
      unknown++;
    }
  }

  // Test; do pretty printing instead
  // std::cout<<"\nFor frame " << yCloud->currentFrame <<" , the number of ic= "<<ic<<" , ih= "<<ih<<" interfacial ice= "
  // <<interIce<<" , clathrate= "<<clath<<" , interfacial clathrate= "<<interClath<<" and water= "<<water<<" and the total is "<<total<<"\n";
  // std::cout<<"For frame " << yCloud->currentFrame <<" , ic= "<<(double)ic/(double)total * 100
  // <<"% , ih= "<<(double)ih/(double)total * 100<<"% interfacial ice= "<<(double)interIce/(double)total * 100<<"% and water= "<<(double)water/(double)total * 100<<"% \n";
  // std::cout<<"\n";

  // Print to file
  std::ofstream outputFile;
  outputFile.open(outputFileName, std::ios_base::app);
  outputFile << yCloud->currentFrame << " " << ic << " " << ih << " "
             << interIce << " " << clath << " " << interClath << " " << water
             << " " << total << "\n";
  outputFile.close();

  return 0;
}

/********************************************/ /**
 *  Function that checks if the the atom with atom index
 iatom is interfacial or not 
 ***********************************************/
bool chill::isInterfacial(
    molSys::PointCloud<molSys::Point<double>, double> *yCloud, int iatom,
    int num_staggrd, int num_eclipsd) {
  int nnumNeighbours; // number of nearest neighbours of iatom
  int neighStaggered =
      0;     // number of staggered bonds in the neighbours of iatom
  int jatom; // Index of nearest neighbour

  // Find the number of nearest neighbours
  if (yCloud->pts[iatom].neighList.size() < 4) {
    nnumNeighbours = yCloud->pts[iatom].neighList.size();
  } else {
    nnumNeighbours = 4;
  }

  // INTERFACIAL
  // Condition 1 : only two staggered bonds and at least
  // one neighbor with more than two staggered bonds
  if (num_staggrd == 2) {
    // Loop over the nearest neighbours
    for (int j = 0; j < nnumNeighbours; j++) {
      // Get index of the nearest neighbour
      jatom = yCloud->pts[iatom].neighList[j];
      neighStaggered = chill::numStaggered(yCloud, jatom);
      if (neighStaggered > 2) {
        return true;
      }
    } // End loop over nearest neighbours
  }   // end condition 1
  // Condition 2 : three staggered bonds, no eclipsed bond,
  // and at least one neighbor with two staggered bonds
  if (num_staggrd == 3 && num_eclipsd == 0) {
    // Loop over the nearest neighbours
    for (int j = 0; j < nnumNeighbours; j++) {
      // Get index of the nearest neighbour
      jatom = yCloud->pts[iatom].neighList[j];
      neighStaggered = chill::numStaggered(yCloud, jatom);
      if (neighStaggered == 2) {
        return true;
      }
    }
  }
  // not interfacial
  return false;
}

/********************************************/ /**
 *  Returns the number of staggered bonds of an atom
 of index jatom 
 ***********************************************/
int chill::numStaggered(
    molSys::PointCloud<molSys::Point<double>, double> *yCloud, int jatom) {
  int num_staggrd = 0;        // Number of staggered bonds
  molSys::bond_type bondType; // Bond type
  int num_bonds;              // No. of bonds of the jatom
  //
  // Find the number of bonds
  if (yCloud->pts[jatom].neighList.size() < 4) {
    num_bonds = yCloud->pts[jatom].neighList.size();
  } else {
    num_bonds = 4;
  }

  // Loop over all bonds
  for (int i = 0; i < num_bonds; i++) {
    bondType = yCloud->pts[jatom].c_ij[i].classifier;
    // If the bond is staggered increment the number of staggered bonds
    if (bondType == molSys::staggered) {
      num_staggrd++;
    }
  } // end of loop over c_ij

  return num_staggrd;
}
