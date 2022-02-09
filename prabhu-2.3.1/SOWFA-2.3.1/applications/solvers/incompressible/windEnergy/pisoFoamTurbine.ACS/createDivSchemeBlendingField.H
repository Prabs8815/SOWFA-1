    Info << "NEW VERSION: Creating divergence scheme blending factor field, UBlendingFactor..." << endl;
    surfaceScalarField UBlendingFactor
    (
        IOobject
        (
            "UBlendingFactor",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        1.0 
    );


    // Read blending information
    List<List<scalar> > profileTable(mesh.schemesDict().subDict("schemeBlending").lookup("faceSizeBlendingTable"));
    scalarField faceAreaList(profileTable.size(),0.0);
    scalarField UBlendingList(profileTable.size(),0.0);

    forAll(faceAreaList,i)
    {
        faceAreaList[i] = profileTable[i][0];
        UBlendingList[i] = profileTable[i][1];
    }

    // Create the old value of these quantities for checking for updated files.
    List<List<scalar> > profileTableOld = profileTable;

    // Create blending factor field
    // internal field
    forAll(UBlendingFactor, faceI)
    {
	scalar area = mesh.magSf()[faceI];
	UBlendingFactor[faceI] = max(min(interpolateSplineXY(area,faceAreaList,UBlendingList),1.0),0.0);

    }

   // boundary field
    forAll(UBlendingFactor.boundaryField(), patchI)
    {
        forAll(UBlendingFactor.boundaryField()[patchI], faceI)
        {
            scalar area = mesh.boundary()[patchI].magSf()[faceI];

            UBlendingFactor.boundaryField()[patchI][faceI] = max(min(interpolateSplineXY(area,faceAreaList,UBlendingList),1.0),0.0);

        }
    }
