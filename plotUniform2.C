// Simple ROOT macro to plot a histogram.
// Modify arguments as needed.
// To execute, type .X plotUniform.C
{
  TFile* f = new TFile("simpleMC.root");
  f->ls();
  TH1D* h3 = (TH1D*)f->Get("h_Uniform3");
  h3->SetMinimum(0.);
  h3->SetXTitle("(E) photon energy [ev]");
  h3->SetYTitle("lambda(E)");
  h3->Draw();
}
