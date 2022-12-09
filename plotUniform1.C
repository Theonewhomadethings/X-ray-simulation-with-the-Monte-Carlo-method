/ Simple ROOT macro to plot a histogram.
// Modify arguments as needed.
// To execute, type .X plotUniform.C
{
  TFile* f = new TFile("simpleMC.root");
  f->ls();
  TH1D* h2 = (TH1D*)f->Get("h_Uniform2");
  h2->SetMinimum(0.);
  h2->SetXTitle("(E) photon energy [ev]");
  h2->SetYTitle("F(E)");
  h2->Draw();
}
