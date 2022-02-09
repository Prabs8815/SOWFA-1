    // Re-read blending information
    List<List<scalar> > profileTable(mesh.schemesDict().subDict("schemeBlending").lookup("faceSizeBlendingTable"));
    forAll(faceAreaList,i)
    {
        faceAreaList[i] = profileTable[i][0];
        UBlendingList[i] = profileTable[i][1];
    }

    // Check to see if the blending factors or face sizes have changed.  If so, recalculate the U and T
    // blending factor field.
    if (profileTable != profileTableOld)
    {


        // Write a message to the log file.
        Info << "Updating scheme blending factor field..." << endl;


        // Update the old value of these quantities for checking for updated files.
        profileTableOld = profileTable;

        // Update the blending factor fields.
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
    }
