{
  /*
  Run from the command line with
  root -l -b RA2bZinvLoadClasses.C RA2bZinvDriver.C
  */

  bool doCCzvv = false;
  bool doCCttzvv = false;
  bool do1Dzvv = false;
  bool do1Dttzvv = false;
  bool do1Dzmm = true;
  bool do1Dzee = true;
  bool doMakeClass = false;

  RA2bZinvAnalysis* analyzer = new RA2bZinvAnalysis();

  if (doCCzvv || doCCttzvv) {
    // Output file
    TFile *CChistos = TFile::Open("hCCzinv.root", "RECREATE");

    if (doCCzvv) {
      TH1F* hCCzvv = analyzer->makeCChist("zinv");
      hCCzvv->SetName("hCCzvv");  hCCzvv->Draw();
    }
    if (doCCttzvv) {
      TH1F* hCCttzvv = analyzer->makeCChist("ttzvv");
      hCCttzvv->SetName("hCCttzvv");  hCCttzvv->Draw();
    }
    if (doCCzvv && doCCttzvv) {
      TH1F* hCCzinv = (TH1F*) hCCzvv->Clone();
      hCCzinv->Add(hCCttzvv);
      hCCzinv->SetName("hCCzinv");  hCCzinv->Draw();
    }
    CChistos->Write();
  }

  if (do1Dzvv || do1Dttzvv) {
    TFile *histos1D = TFile::Open("histsZjets.root", "RECREATE");
    if (do1Dzvv) {
      std::vector<TH1F*> h_zinv = analyzer->makeHistograms("zinv");
      for (auto& theHist : h_zinv) theHist->Draw();
    }
    if (do1Dttzvv) {
      std::vector<TH1F*> h_ttzvv = analyzer->makeHistograms("ttzvv");
      for (auto& theHist : h_ttzvv) theHist->Draw();
    }
    histos1D->Write();
  }

  if (do1Dzmm || do1Dzee) {
    TFile *histos1D = TFile::Open("histsDY.root", "RECREATE");
    if (do1Dzmm) {
      std::vector<TH1F*> h_zmm = analyzer->makeHistograms("zmm");
      for (auto& theHist : h_zmm) theHist->Draw();
    }
    if (do1Dzee) {
      std::vector<TH1F*> h_zee = analyzer->makeHistograms("zee");
      for (auto& theHist : h_zee) theHist->Draw();
    }
    histos1D->Write();
  }

  if (doMakeClass) analyzer->runMakeClass("zmm", "data_V12");

  gApplication->Terminate(0);

}