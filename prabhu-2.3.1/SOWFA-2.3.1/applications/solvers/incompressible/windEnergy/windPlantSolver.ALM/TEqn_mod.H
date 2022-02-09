{
    kappat = turbulence->nut()/Prt;
    kappat.correctBoundaryConditions();

    volScalarField kappaEff("kappaEff", turbulence->nu()/Pr + kappat);

    fvScalarMatrix TEqn
    (
        fvm::ddt(T)
      + fvm::div(phi, T)
      - fvm::laplacian(kappaEff, T)
      - fvc::div(qwall)
      - SourceT
     == //---new line
       fvOptions(T) //---new line
    );

    TEqn.relax();
    fvOptions.constrain(TEqn); //---new line
    TEqn.solve();
    fvOptions.correct(T); //---new line

    rhok = 1.0 - ( (T - TRef)/TRef );
}
