/*-----------------------------------
By Gonzalo Pablo Navarro Diaz - 2020
gonzalo.navarro@geo.uu.se

This file compute the thrust force for the forest model:

forestF = Cd*a_*|U|*U

forestF: Forest force [m/s2] (no density multiplication [kg/m3] )
Cd: Forest Drag coefficient (Cd=0.2 recomendation)
a_: Plant Area Density [m2/m3]=[1/m]
|U|: velocity magnitude [m/s]
U: velocity vector [m/s]

----------------------------------*/

forestF = -0.2*a_*mag(U)*U; //oposite to the wind, like a wind turbine. reduce the velocity

/*
//other option for calculation
forAll(forestF,cellI)
{
  forestF[cellI].x() = -0.2*a_[cellI]*mag(U[cellI].x())*U[cellI].x();
  forestF[cellI].y() = -0.2*a_[cellI]*mag(U[cellI].y())*U[cellI].y();
  forestF[cellI].z() = -0.2*a_[cellI]*mag(U[cellI].z())*U[cellI].z();
}

*/
