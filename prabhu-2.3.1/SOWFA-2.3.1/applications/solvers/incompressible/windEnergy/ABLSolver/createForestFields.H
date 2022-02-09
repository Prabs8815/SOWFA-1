/*-----------------------------------
By Gonzalo Pablo Navarro Diaz - 2020
gonzalo.navarro@geo.uu.se

This file creates the filds for the forest model:

1- Plant Area Density "a_" [m2/m3]
2- Forest force "forestF" [m/s2] (no density multiplication [kg/m3] ) 

----------------------------------*/


    //Create the Plant Area Density field "a_" for the forest model
    Info << "Creating the Plant Area Density field a_ for the forest model..." << endl;
    volScalarField a_
    (
        IOobject
        (
            "a_",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE //output for paraview
        ),
        mesh,
        dimensionedScalar
        (
            "a_",
            dimensionSet(0,-1,0,0,0,0,0),//(kg, m, s, K, mol, A, cd)
            0.0 //fill the field with cero values in all cells
        ) 
    );

    //Create the volumetric forest force "forestF"
    Info << "Creating the forest force forestF for the forest model..." << endl;
    volVectorField forestF
    (
        IOobject
        (
            "forestF",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector
        (
            "forestF",
            dimensionSet(0, 1, -2, 0, 0, 0, 0),// same as coriolis force (m/s2) (kg, m, s, K, mol, A, cd)
            vector::zero
        )
    );

