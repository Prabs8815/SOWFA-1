    // Solve the momentum equation

    #include "computeCoriolisForce.H"
    #include "computeForestForce.H" //---new line

    fvVectorMatrix UEqn
    (
        fvm::ddt(U)                             // time derivative
      + fvm::div(phi, U)                        // convection
      + turbulence->divDevReff(U)               // momentum flux
      + fvc::div(Rwall)
      - fCoriolis                               // Coriolis force
      //- turbines.force()                        // turbine body forces //---new line
      - SourceU                                 // mesoscale source terms
      - forestF                                 //forest thurst force //---new line
      //==                 //---new line
      - fvOptions(U)    //---new line
    );

    UEqn.relax();

    //fvOptions.constrain(UEqn);//---new line

    if (pimple.momentumPredictor())
    {
        solve
        (
            UEqn
            ==
            fvc::reconstruct
            (
                (
                  - fvc::snGrad(p_rgh)          // modified pressure gradient
                  - ghf*fvc::snGrad(rhok)       // buoyancy force
                ) * mesh.magSf()
            )
        );

        //fvOptions.correct(U); //---new line

    }
