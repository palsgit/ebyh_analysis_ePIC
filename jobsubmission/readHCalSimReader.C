// Code to draw Basic Tracking Performances
// Shyam Kumar:INFN Bari, shyam.kumar@ba.infn.it; shyam055119@gmail.com

#include "TGraphErrors.h"
#include "TF1.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"

/*Double_t fgaus(Double_t *x, Double_t *par) {
	return par[0]/(TMath::Sqrt(2*TMath::Pi()*par[2]*par[2]))*TMath::Exp(-(x[0]-par[1])*(x[0]-par[1])/(2*par[2]*par[2]));
	
}*/

void readHCalSimReader(TString inFileName, TString outFileName)
{

//==========Style of the plot============
   gStyle->SetPalette(1);
   gStyle->SetOptTitle(1);
   gStyle->SetTitleOffset(.85,"X");gStyle->SetTitleOffset(.85,"Y");
   gStyle->SetTitleSize(.04,"X");gStyle->SetTitleSize(.04,"Y");
   gStyle->SetLabelSize(.04,"X");gStyle->SetLabelSize(.04,"Y");
   gStyle->SetHistLineWidth(2);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   char *parstring = new char[50];
//=======Reading the root file DD4HEP===========
   TFile* file = new TFile(inFileName); // Tree with tracks and hits
		// Create the tree reader and its data containers
   TTreeReader myReader("events", file); // name of tree and file
	 
   TFile *output = new TFile(outFileName, "recreate");

   TTreeReaderArray<Float_t> charge(myReader, "MCParticles.charge"); 
   TTreeReaderArray<Double_t> vx_mc(myReader, "MCParticles.vertex.x"); 
   TTreeReaderArray<Double_t> vy_mc(myReader, "MCParticles.vertex.y"); 
   TTreeReaderArray<Double_t> vz_mc(myReader, "MCParticles.vertex.z"); 
   TTreeReaderArray<Float_t> px_mc(myReader, "MCParticles.momentum.x"); 
   TTreeReaderArray<Float_t> py_mc(myReader, "MCParticles.momentum.y"); 
   TTreeReaderArray<Float_t> pz_mc(myReader, "MCParticles.momentum.z"); 
   TTreeReaderArray<Int_t> status(myReader, "MCParticles.generatorStatus"); 
   TTreeReaderArray<Double_t> mass(myReader, "MCParticles.mass"); 
   TTreeReaderArray<Double_t> endx_mc(myReader, "MCParticles.endpoint.x"); 
   TTreeReaderArray<Double_t> endy_mc(myReader, "MCParticles.endpoint.y"); 
   TTreeReaderArray<Double_t> endz_mc(myReader, "MCParticles.endpoint.z"); 
    
   /*TTreeReaderArray<Float_t> ECalEndCapNhit_x(myReader, "EcalEndcapNHits.position.x"); 
   TTreeReaderArray<Float_t> ECalEndCapNhit_y(myReader, "EcalEndcapNHits.position.y"); 
   TTreeReaderArray<Float_t> ECalEndCapNhit_z(myReader, "EcalEndcapNHits.position.z");*/
   

   TTreeReaderArray<Float_t> HCalEndCapNhit_x(myReader, "HcalEndcapNHits.position.x"); 
   TTreeReaderArray<Float_t> HCalEndCapNhit_y(myReader, "HcalEndcapNHits.position.y"); 
   TTreeReaderArray<Float_t> HCalEndCapNhit_z(myReader, "HcalEndcapNHits.position.z");
   TTreeReaderArray<Float_t> HCalEndCapNhit_E(myReader, "HcalEndcapNHits.energy");

   /*TTreeReaderArray<Float_t> HcalBarrelhit_x(myReader, "HcalBarrelHits.position.x"); 
   TTreeReaderArray<Float_t> HcalBarrelhit_y(myReader, "HcalBarrelHits.position.y"); 
   TTreeReaderArray<Float_t> HcalBarrelhit_z(myReader, "HcalBarrelHits.position.z");

   TTreeReaderArray<Float_t> EcalBarrelImaginghit_x(myReader, "EcalBarrelImagingHits.position.x"); 
   TTreeReaderArray<Float_t> EcalBarrelImaginghit_y(myReader, "EcalBarrelImagingHits.position.y"); 
   TTreeReaderArray<Float_t> EcalBarrelImaginghit_z(myReader, "EcalBarrelImagingHits.position.z");

   TTreeReaderArray<Float_t> EcalBarrelScFihit_x(myReader, "EcalBarrelScFiHits.position.x"); 
   TTreeReaderArray<Float_t> EcalBarrelScFihit_y(myReader, "EcalBarrelScFiHits.position.y"); 
   TTreeReaderArray<Float_t> EcalBarrelScFihit_z(myReader, "EcalBarrelScFiHits.position.z");
   */
   
 
 /*const int ngraph = 16; 
 TCanvas * c[ngraph]; 
 for (int i =0; i<ngraph; ++i){
 c[i] = new TCanvas(Form("c%d",i),Form("c%d",i),1200,1000);
 c[i]->SetMargin(0.09, 0.1 ,0.1,0.06);
 }

 // X-Y Hits

 
 TH2D *heff_pnum = new TH2D("heff_pnum","heff_p",1500,0.,10.0,nbins,-x,x);
 TH2D *heff_pden = new TH2D("heff_pden","heff_p",1500,0.,10.0,nbins,-x,x);
 
 TH2D *hetavsptgen = new TH2D("hetavsptgen","hetavsptgen",1500,0.,10.0,nbins,-x,x);
 TH2D *heff_ptnum = new TH2D("heff_ptnum","heff_p",1500,0.,10.0,nbins,-x,x);
 TH2D *heff_ptden = new TH2D("heff_ptden","heff_p",1500,0.,10.0,nbins,-x,x);

 TH1D *h_NEcal_hits_pos_x = new TH1D("h_NEcal_hits_pos_x", "NEcal-hits position x; x [mm]; counts", 1000, -5000.0, 5000.0);
 TH1D *h_NEcal_hits_pos_y = new TH1D("h_NEcal_hits_pos_y", "NEcal-hits position y; y [mm]; counts", 1000, -5000.0, 5000.0);
 TH1D *h_NEcal_hits_pos_z = new TH1D("h_NEcal_hits_pos_z", "NEcal-hits position z; z [mm]; counts", 1000, -5000.0, 5000.0);
 TH2D *h_NEcal_hits_pos_xy = new TH2D("h_NEcal_hits_pos_xy", "NEcal-hits position x,y; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
 TH2D *h_NEcal_hits_pos_zr = new TH2D("h_NEcal_hits_pos_zr", "NEcal-hits position z,r; z [mm]; r [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
 TH2D *h_NEcal_hits_etaphi = new TH2D("h_NEcal_hits_etaphi", "NEcal-hits #eta,#phi; #eta; #phi [rad]; counts", 200, -7.6, 7.6, 3140, -TMath::Pi(), TMath::Pi());

 TH1D *h_NHcal_hits_pos_x = new TH1D("h_NHcal_hits_pos_x", "NHcal-hits position x; x [mm]; counts", 1000, -5000.0, 5000.0);
 TH1D *h_NHcal_hits_pos_y = new TH1D("h_NHcal_hits_pos_y", "NHcal-hits position y; y [mm]; counts", 1000, -5000.0, 5000.0);
 TH1D *h_NHcal_hits_pos_z = new TH1D("h_NHcal_hits_pos_z", "NHcal-hits position z; z [mm]; counts", 1000, -5000.0, 5000.0);*/

 Int_t nbins = 2000;
 Double_t x= 50.0;  
 TH2D *hetavspgen = new TH2D("hetavspgen","Gen #eta vs p; p [GeV]; #eta ;",1500,0.,10.0,nbins,-x,x);
 TH2D *hphivsmassgen = new TH2D("hphivsmassgen","Gen #phi vs Mass; Mass [GeV]; #phi [rad]; ",nbins,-1,1, 3140, -TMath::Pi(), TMath::Pi());
 TH2D *hvzvschargegen = new TH2D("hvzvschargegen","Gen Vertex z vs charge; charge; V_{z} [mm]",nbins,-5,5,nbins,-x,x);
 TH2D *hvyvsvxgen = new TH2D("hvyvsvxgen", "Gen Vertex x,y; V_{x} [mm]; V_{y} [mm]; counts", nbins,-x,x,nbins,-x,x);
 TH2D *h_genendpos_zr = new TH2D("h_genendpos_zr", " Gen End position z,r; z [mm]; r [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
 TH2D *h_secendpos_zr = new TH2D("h_secendpos_zr", " Secondary MC End position z,r; z [mm]; r [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
 

 TH2D *h_NHcal_hits_pos_xy = new TH2D("h_NHcal_hits_pos_xy", "NHcal-hits position x,y; x [mm]; y [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
 TH2D *h_NHcal_hits_pos_zr = new TH2D("h_NHcal_hits_pos_zr", "NHcal-hits position z,r; z [mm]; r [mm]; counts", 1000, -5000.0, 5000.0, 1000, -5000.0, 5000.0);
 TH2D *h_NHcal_hits_etaphi = new TH2D("h_NHcal_hits_etaphi", "NHcal-hits #eta,#phi; #eta; #phi [rad]; counts", 200, -7.6, 7.6, 3140, -TMath::Pi(), TMath::Pi());
 TH1D *h_NHcal_hit_E_perevent = new TH1D("h_NHcal_hit_E_perevent", "NHcal-hit energy per event; #Sigma E_{hit} [GeV]; Entries", 5000, 0.0, 1.0);
 

 /*TH2D *h_BarrelHcal_hits_etaphi = new TH2D("h_BarrelHcal_hits_etaphi", "BarrelHcal-hits #eta,#phi; #eta; #phi [rad]; counts", 200, -7.6, 7.6, 3140, -TMath::Pi(), TMath::Pi());
 TH2D *h_BarrelEcalImaging_hits_etaphi = new TH2D("h_BarrelEcalImaging_hits_etaphi", "BarrelEcalImaging-hits #eta,#phi; #eta; #phi [rad]; counts", 200, -7.6, 7.6, 3140, -TMath::Pi(), TMath::Pi());
 TH2D *h_BarrelEcalScFi_hits_etaphi = new TH2D("h_BarrelEcalScFi_hits_etaphi", "BarrelEcalScFi-hits #eta,#phi; #eta; #phi [rad]; counts", 200, -7.6, 7.6, 3140, -TMath::Pi(), TMath::Pi());

 
 TH1D *hpz = new TH1D("hpz","hpz",200,-5.5,5.5);
 
 hetavspgen->GetXaxis()->SetTitle("p_{gen} (GeV/c)");
 hetavspgen->GetYaxis()->SetTitle("#eta_{gen}");
 hetavspgen->GetXaxis()->CenterTitle();
 hetavspgen->GetYaxis()->CenterTitle();
 
 hetavsptgen->GetXaxis()->SetTitle("pt_{gen} (GeV/c)");
 hetavsptgen->GetYaxis()->SetTitle("#eta_{gen}");
 hetavsptgen->GetXaxis()->CenterTitle();
 hetavsptgen->GetYaxis()->CenterTitle();
 
 
 hpz->GetXaxis()->SetTitle("p_{z}");
 hpz->GetYaxis()->SetTitle("Counts");
 hpz->GetXaxis()->CenterTitle();
 hpz->GetYaxis()->CenterTitle();*/
 


//////////////////////////////////////////////////////////////////////

  Int_t nEvents = myReader.GetEntries();
  cout<<"Total Events: "<<nEvents<<endl;

 

  for (Int_t iEvent = 0; iEvent<nEvents; ++iEvent)
  {
     myReader.SetEntry(iEvent);
     if (iEvent%1000==0) cout<<"Event No: "<<iEvent<<endl;
     Double_t pmc = 0;  Double_t etamc = 0; Double_t ptmc = 0;
     Double_t thetamc;
	   Double_t phimc;

     /*Double_t thetareco;
	   Double_t phireco;
     Double_t thetaNhcal;
	   Double_t phiNhcal;
     Double_t thetaNecal;
	   Double_t phiNecal;

     Double_t xreco;
	   Double_t yreco;
     Double_t xNhcal;
	   Double_t yNhcal;
     Double_t xNecal;
	   Double_t yNecal;*/

     Double_t nhcal_hitEtotal = 0.0;
     

     /*Double_t eNhcal;
     Double_t eNecal;
     Double_t eReco;*/

   // MC Particle
     for (int iParticle = 0; iParticle < charge.GetSize(); ++iParticle){
   //  cout<<" PDG: "<<pdg[iParticle]<<" Status: "<<status[iParticle]<<" Pt: "<<sqrt(px_mc[iParticle]*px_mc[iParticle]+py_mc[iParticle]*py_mc[iParticle])<<endl;
     if (status[iParticle] ==1){
     pmc = sqrt(px_mc[iParticle]*px_mc[iParticle]+py_mc[iParticle]*py_mc[iParticle]+pz_mc[iParticle]*pz_mc[iParticle]);
     ptmc = sqrt(px_mc[iParticle]*px_mc[iParticle]+py_mc[iParticle]*py_mc[iParticle]);
     etamc = -1.0*TMath::Log(TMath::Tan((TMath::ACos(pz_mc[iParticle]/pmc))/2)); 
     thetamc = TMath::ACos(pz_mc[iParticle]/pmc);
	   phimc = TMath::ATan(py_mc[iParticle]/px_mc[iParticle]);
     
     //////cout << "thetamc" << "  " << 2.96706 << "   " << "phimc" << "  " << 0.785398 << "   " << "First" << endl;
     hetavspgen->Fill(pmc,etamc);
     hphivsmassgen->Fill(mass[iParticle],phimc);
     hvzvschargegen->Fill(charge[iParticle],vz_mc[iParticle]);
     hvyvsvxgen->Fill(vx_mc[iParticle],vy_mc[iParticle]);
     h_genendpos_zr->Fill(endz_mc[iParticle], (sqrt(pow(endx_mc[iParticle],2)+pow(endy_mc[iParticle],2))));
     ///heff_pden->Fill(pgen,etagen);
     ///heff_ptden->Fill(ptgen,etagen);  
     ///hpz->Fill(pz_mc[iParticle]);
     /*if (px_rec.GetSize()==1){
     Double_t prec = sqrt(px_rec[iParticle]*px_rec[iParticle]+py_rec[iParticle]*py_rec[iParticle]+pz_rec[iParticle]*pz_rec[iParticle]);
     Double_t ptrec = sqrt(px_rec[iParticle]*px_rec[iParticle]+py_rec[iParticle]*py_rec[iParticle]);
     Double_t etarec = -1.0*TMath::Log(TMath::Tan((TMath::ACos(pz_rec[iParticle]/prec))/2)); 
     h_NHcal_cluster_theta->Fill(prec,etarec);
     h_NHcal_cluster_phi->Fill(ptrec,etarec);
     
     heff_pnum->Fill(pmc,etamc);
     heff_ptnum->Fill(ptmc,etamc);  
     }*/
     }

     if (status[iParticle] !=1) {
       h_secendpos_zr->Fill(endz_mc[iParticle], (sqrt(pow(endx_mc[iParticle],2)+pow(endy_mc[iParticle],2))));
     }
     }

      /*for (int iParticle = 0; iParticle < ECalEndCapNhit_x.GetSize(); ++iParticle){
     h_NEcal_hits_pos_x->Fill(ECalEndCapNhit_x[iParticle]);
		 h_NEcal_hits_pos_y->Fill(ECalEndCapNhit_y[iParticle]);
		 h_NEcal_hits_pos_z->Fill(ECalEndCapNhit_z[iParticle]);

     h_NEcal_hits_pos_xy->Fill(ECalEndCapNhit_x[iParticle], ECalEndCapNhit_y[iParticle]);
					//h_NEcal_hits_pos_xyz->Fill(ECalEndCapNhit_x[iParticle], ECalEndCapNhit_y[iParticle], ECalEndCapNhit_z[iParticle]);
		 h_NEcal_hits_pos_zr->Fill(ECalEndCapNhit_z[iParticle], (sqrt(pow((ECalEndCapNhit_x[iParticle]),2)+pow((ECalEndCapNhit_y[iParticle]),2))));
					
     TVector3 hitpos(ECalEndCapNhit_x[iParticle], ECalEndCapNhit_y[iParticle], ECalEndCapNhit_z[iParticle]);
     h_NEcal_hits_etaphi->Fill(hitpos.Eta(),hitpos.Phi());
      }*/


      for (int iParticle = 0; iParticle < HCalEndCapNhit_x.GetSize(); ++iParticle){
     /*h_NHcal_hits_pos_x->Fill(HCalEndCapNhit_x[iParticle]);
		 h_NHcal_hits_pos_y->Fill(HCalEndCapNhit_y[iParticle]);
		 h_NHcal_hits_pos_z->Fill(HCalEndCapNhit_z[iParticle]);*/

     h_NHcal_hits_pos_xy->Fill(HCalEndCapNhit_x[iParticle], HCalEndCapNhit_y[iParticle]);
					//h_NHcal_hits_pos_xyz->Fill(HCalEndCapNhit_x[iParticle], HCalEndCapNhit_y[iParticle], HCalEndCapNhit_z[iParticle]);
		 h_NHcal_hits_pos_zr->Fill(HCalEndCapNhit_z[iParticle], (sqrt(pow((HCalEndCapNhit_x[iParticle]),2)+pow((HCalEndCapNhit_y[iParticle]),2))));
					
     TVector3 hitpos(HCalEndCapNhit_x[iParticle], HCalEndCapNhit_y[iParticle], HCalEndCapNhit_z[iParticle]);
     h_NHcal_hits_etaphi->Fill(hitpos.Eta(),hitpos.Phi());

     nhcal_hitEtotal += HCalEndCapNhit_E[iParticle];
      }

      /*for (int iParticle = 0; iParticle < HcalBarrelhit_x.GetSize(); ++iParticle){
     TVector3 hitpos(HcalBarrelhit_x[iParticle], HcalBarrelhit_y[iParticle], HcalBarrelhit_z[iParticle]);
     h_BarrelHcal_hits_etaphi->Fill(hitpos.Eta(),hitpos.Phi());
      }

      for (int iParticle = 0; iParticle < EcalBarrelImaginghit_x.GetSize(); ++iParticle){
     TVector3 hitpos(EcalBarrelImaginghit_x[iParticle], EcalBarrelImaginghit_y[iParticle], EcalBarrelImaginghit_z[iParticle]);
     h_BarrelEcalImaging_hits_etaphi->Fill(hitpos.Eta(),hitpos.Phi());
      }

      for (int iParticle = 0; iParticle < EcalBarrelScFihit_x.GetSize(); ++iParticle){
     TVector3 hitpos(EcalBarrelScFihit_x[iParticle], EcalBarrelScFihit_y[iParticle], EcalBarrelScFihit_z[iParticle]);
     h_BarrelEcalScFi_hits_etaphi->Fill(hitpos.Eta(),hitpos.Phi());
      }*/
     

     h_NHcal_hit_E_perevent->Fill(nhcal_hitEtotal);
     


     


  } // Event For loop

  cout<<"Writing histograms"<<endl;
    /*
	  h_MCpart_1stgen_neutron->Write();
	  h_MCpart_2ndgen_neutron->Write();
	  h_MCpart_3rdgen_neutron->Write();
	  */
	  //h_MCpart_sec_posEnd_zr_isnotDecayedInCalorimeter->Write();
	  //hist_3d->Write();
	   output->Write();

  /*TCanvas *sampfrac = new TCanvas("sampfrac");
  sampfrac->cd();
  TF1 *fitfunc = new TF1("fitfunc", fgaus, 0.02, 0.08, 3);
	fitfunc->SetParameters(3.64102e+03, 0.05, 0.04);
  fitfunc->SetParNames("Area", "Mean", "Sigma");
  ////h_NHcal_hit_E_perevent->GetXaxis()->SetRangeUser(0.0, 0.3);
	//h_NHcal_hit_E_perevent->GetYaxis()->SetRangeUser(0.0, 6.0);
	h_NHcal_hit_E_perevent->SetMarkerStyle(28);
  h_NHcal_hit_E_perevent->SetMarkerSize(2);
	h_NHcal_hit_E_perevent->Fit("fitfunc", "MR", "", 0.02, 0.08);
	h_NHcal_hit_E_perevent->Draw("p");

  TLatex tl;
	tl.SetTextSize(0.1);
	tl.SetTextColor(2);
  tl.DrawLatex(0.05,0.7,parstring);
	sprintf(parstring,"Hit Energy Sum Distribution");	
  tl.DrawLatex(0.05,0.55,parstring);
	sprintf(parstring,"#pi^{-} in nHCal+Vacuum");	
	tl.DrawLatex(0.05,0.4,parstring);
   sprintf(parstring,"#chi^{2}/ndf = %.3f/%i",fitfunc->GetChisquare(),fitfunc->GetNDF());
	///hist1->Fit("gaus", "MR", "", 1.85, 1.91);
	

  
     /* heff_pnum->Divide(heff_pden);
      heff_ptnum->Divide(heff_ptden);
      heff_pnum->GetYaxis()->SetTitle("Acceptance");
      heff_pnum->GetXaxis()->SetTitle("p_mc");
      heff_pnum->GetZaxis()->SetRangeUser(0.,1.1);
      
      heff_ptnum->GetYaxis()->SetTitle("Acceptance");
      heff_ptnum->GetXaxis()->SetTitle("pt_mc");
      heff_ptnum->GetZaxis()->SetRangeUser(0.,1.1);
      */

      

  
     /*c[0]->cd();
     hetavspgen->Draw("colz");
     c[0]->SaveAs("eta_genvspgen.png");

     c[1]->cd();
     hetavsptgen->Draw("colz");
     c[1]->SaveAs("eta_genvsptgen.png");*/
      
}
