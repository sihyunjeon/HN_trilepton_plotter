void canvas_margin(TCanvas *c1){
  c1->SetTopMargin( 0.05 );
  c1->SetBottomMargin( 0.13 );
  c1->SetRightMargin( 0.05 );
  c1->SetLeftMargin( 0.16 );

}

void canvas_margin(TCanvas *c1, TPad *c1_up, TPad *c1_down){
  c1_up->SetTopMargin( 0.07 );
  c1_up->SetBottomMargin( 0.02 );
  c1_up->SetLeftMargin( 0.15 );
  c1_up->SetRightMargin( 0.03 );

  c1_down->SetTopMargin( 0.03 );
  c1_down->SetBottomMargin( 0.4 );
  c1_down->SetLeftMargin( 0.15 );
  c1_down->SetRightMargin( 0.03 );
  c1_down->SetGridx();
  c1_down->SetGridy();
  
  c1->SetTopMargin( 0.05 );
  c1->SetBottomMargin( 0.13 );
  c1->SetRightMargin( 0.05 );
  c1->SetLeftMargin( 0.16 );

}

void hist_axis(TH1D *hist){

  hist->SetTitle("");

  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetTitleOffset(1.02);

  hist->GetXaxis()->SetLabelSize(0.03);
  hist->GetXaxis()->SetTitleSize(0.05);

}

void hist_axis(THStack *hist){

  hist->SetTitle("");

  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetTitleOffset(1.02);

  hist->GetXaxis()->SetLabelSize(0.03);
  hist->GetXaxis()->SetTitleSize(0.05);

}

void hist_axis(TGraph *hist){

  hist->SetTitle("");

  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetTitleOffset(1.02);

  hist->GetXaxis()->SetLabelSize(0.03);
  hist->GetXaxis()->SetTitleSize(0.05);

}

void hist_axis(TGraphAsymmErrors *hist){

  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetTitleOffset(1.02);

  hist->GetXaxis()->SetLabelSize(0.03);
  hist->GetXaxis()->SetTitleSize(0.05);

}

void hist_axis(TH2D *hist){

  hist->SetTitle("");

  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetTitleOffset(1.02);

  hist->GetXaxis()->SetLabelSize(0.03);
  hist->GetXaxis()->SetTitleSize(0.05);

}

void hist_axis(THStack *hist, TH1D *hist_compare){

  hist->SetTitle("");

  //==== top plot
  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetTitleOffset(1.02);
  //==== hide x-axis for top plot
  hist->GetXaxis()->SetLabelSize(0);

  //==== bottom plot
  hist_compare->SetTitle("");
  hist_compare->GetXaxis()->SetLabelSize(0.10);
  hist_compare->GetXaxis()->SetTitleSize(0.15);
  hist_compare->GetYaxis()->SetLabelSize(0.08);
  hist_compare->GetYaxis()->SetTitleSize(0.12);
  hist_compare->GetYaxis()->SetTitleOffset(0.5);
  hist_compare->SetFillColorAlpha(45,0.35);

}

void hist_axis(TH1D *hist, TH1D *hist_compare){

  hist->SetTitle("");

  //==== top plot
  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetTitleOffset(1.02);
  //==== hide x-axis for top plot
  hist->GetXaxis()->SetLabelSize(0);

  //==== bottom plot
  hist_compare->SetTitle("");
  hist_compare->GetXaxis()->SetLabelSize(0.10);
  hist_compare->GetXaxis()->SetTitleSize(0.15);
  hist_compare->GetYaxis()->SetLabelSize(0.08);
  hist_compare->GetYaxis()->SetTitleSize(0.12);
  hist_compare->GetYaxis()->SetTitleOffset(0.5);
  hist_compare->SetFillColorAlpha(45,0.35);

}

void hist_axis(TGraph *hist, TGraph *hist_compare){

  hist->SetTitle("");

  //==== top plot
  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetTitleOffset(1.02);
  //==== hide x-axis for top plot
  hist->GetXaxis()->SetLabelSize(0);

  //==== bottom plot
  hist_compare->SetTitle("");
  hist_compare->GetXaxis()->SetLabelSize(0.10);
  hist_compare->GetXaxis()->SetTitleSize(0.15);
  hist_compare->GetYaxis()->SetLabelSize(0.08);
  hist_compare->GetYaxis()->SetTitleSize(0.12);
  hist_compare->GetYaxis()->SetTitleOffset(0.5);
  hist_compare->SetFillColorAlpha(45,0.35);

}
