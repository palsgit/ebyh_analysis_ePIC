#include <TFile.h>
#include <TGraphErrors.h>
#include <TCanvas.h>

void ebyh_ratio(const char* file1 = "e-high_energy.root", const char* file2 = "pi-high_energy.root", const char* graphName = "MeanEvsp") {
    // Open the first file
    TFile* f1 = TFile::Open(file1);
    if (!f1) {
        std::cout << "Error opening file: " << file1 << std::endl;
        return;
    }

    // Open the second file
    TFile* f2 = TFile::Open(file2);
    if (!f2) {
        std::cout << "Error opening file: " << file2 << std::endl;
        f1->Close();
        return;
    }

    // Get the TGraphErrors from the first file
    TGraphErrors* graph1 = dynamic_cast<TGraphErrors*>(f1->Get(graphName));
    if (!graph1) {
        std::cout << "Error retrieving graph: " << graphName << " from file: " << file1 << std::endl;
        f1->Close();
        f2->Close();
        return;
    }

    // Get the TGraphErrors from the second file
    TGraphErrors* graph2 = dynamic_cast<TGraphErrors*>(f2->Get(graphName));
    if (!graph2) {
        std::cout << "Error retrieving graph: " << graphName << " from file: " << file2 << std::endl;
        f1->Close();
        f2->Close();
        return;
    }

    // Create a new TGraphErrors for the ratio
    
    

    // Calculate the ratio of the two graphs

        // Find the index i for x = 1
        int a1 = -1;
        int a2 = -1;
        int a5 = -1;
        int a10 = -1;
        int a20 = -1;
        for (int j = 0; j < graph1->GetN(); ++j) {
            if (graph1->GetPointX(j) == 1) {
                a1 = j;
            }
            if (graph1->GetPointX(j) == 2) {
                a2 = j;
            }
            if (graph1->GetPointX(j) == 5) {
                a5 = j;
            }
            if (graph1->GetPointX(j) == 10) {
                a10 = j;
            }
            if (graph1->GetPointX(j) == 20) {
                a20 = j;
            }
        }

        int b1 = -1;
        int b2 = -1;
        int b5 = -1;
        int b10 = -1;
        int b20 = -1;
        for (int j = 0; j < graph2->GetN(); ++j) {
            if (graph2->GetPointX(j) == 1) {
                b1 = j;
            }
            if (graph2->GetPointX(j) == 2) {
                b2 = j;
            }
            if (graph2->GetPointX(j) == 5) {
                b5 = j;
            }
            if (graph2->GetPointX(j) == 10) {
                b10 = j;
            }
            if (graph2->GetPointX(j) == 20) {
                b20 = j;
            }
        }
        
        double ratioArray[5];
        ratioArray[0] = graph1->GetPointY(a1) / graph2->GetPointY(b1);
        ratioArray[1] = graph1->GetPointY(a2) / graph2->GetPointY(b2);
        ratioArray[2] = graph1->GetPointY(a5) / graph2->GetPointY(b5);
        ratioArray[3] = graph1->GetPointY(a10) / graph2->GetPointY(b10);
        ratioArray[4] = graph1->GetPointY(a20) / graph2->GetPointY(b20);
        double ratioErrorArray[5];
        ratioErrorArray[0] = ratioArray[0] * sqrt(pow((graph1->GetErrorY(a1) / graph1->GetPointY(a1)), 2) + pow((graph2->GetErrorY(b1) / graph2->GetPointY(b1)), 2));
        ratioErrorArray[1] = ratioArray[1] * sqrt(pow((graph1->GetErrorY(a2) / graph1->GetPointY(a2)), 2) + pow((graph2->GetErrorY(b2) / graph2->GetPointY(b2)), 2));
        ratioErrorArray[2] = ratioArray[2] * sqrt(pow((graph1->GetErrorY(a5) / graph1->GetPointY(a5)), 2) + pow((graph2->GetErrorY(b5) / graph2->GetPointY(b5)), 2));
        ratioErrorArray[3] = ratioArray[3] * sqrt(pow((graph1->GetErrorY(a10) / graph1->GetPointY(a10)), 2) + pow((graph2->GetErrorY(b10) / graph2->GetPointY(b10)), 2));
        ratioErrorArray[4] = ratioArray[4] * sqrt(pow((graph1->GetErrorY(a20) / graph1->GetPointY(a20)), 2) + pow((graph2->GetErrorY(b20) / graph2->GetPointY(b20)), 2));
        
        /*ratioErrorArray[0] = ratioArray[0] * ((graph1->GetErrorY(a1) / graph1->GetPointY(a1))  - (graph2->GetErrorY(b1) / graph2->GetPointY(b1)));
        ratioErrorArray[1] = ratioArray[1] * ((graph1->GetErrorY(a2) / graph1->GetPointY(a2)) - (graph2->GetErrorY(b2) / graph2->GetPointY(b2)));
        ratioErrorArray[2] = ratioArray[2] * ((graph1->GetErrorY(a5) / graph1->GetPointY(a5)) - (graph2->GetErrorY(b5) / graph2->GetPointY(b5)));
        ratioErrorArray[3] = ratioArray[3] * ((graph1->GetErrorY(a10) / graph1->GetPointY(a10)) - (graph2->GetErrorY(b10) / graph2->GetPointY(b10)));
        ratioErrorArray[4] = ratioArray[4] * ((graph1->GetErrorY(a20) / graph1->GetPointY(a20)) - (graph2->GetErrorY(b20) / graph2->GetPointY(b20)));
        */
        
        double pArray[5] = {1, 2, 5, 10, 20};
        double pErrorArray[5] = {0, 0, 0, 0, 0};
        

        cout << "ratioArray[0] = " << ratioArray[0] << "  " << graph1->GetPointX(a1) << "    " << graph2->GetPointX(b1) << "   "  << graph1->GetPointY(a1) << "    " << graph2->GetPointY(b1) << endl;
        cout << "ratioArray[1] = " << ratioArray[1] << "  " << graph1->GetPointX(a2) << "    " << graph2->GetPointX(b2) << "   "  << graph1->GetPointY(a2) << "    " << graph2->GetPointY(b2) << endl;
        cout << "ratioArray[2] = " << ratioArray[2] << "  " << graph1->GetPointX(a5) << "    " << graph2->GetPointX(b5) << "   "  << graph1->GetPointY(a5) << "    " << graph2->GetPointY(b5) << endl;
        cout << "ratioArray[3] = " << ratioArray[3] << "  " << graph1->GetPointX(a10) << "    " << graph2->GetPointX(b10) << "   "  << graph1->GetPointY(a10) << "    " << graph2->GetPointY(b10) << endl;
        cout << "ratioArray[4] = " << ratioArray[4] << "  " << graph1->GetPointX(a20) << "    " << graph2->GetPointX(b20) << "   "  << graph1->GetPointY(a20) << "    " << graph2->GetPointY(b20) << endl;

        cout << "ratioErrorArray[0] = " << ratioErrorArray[0] << "  " << graph1->GetErrorX(a1) << "    " << graph2->GetErrorX(b1) << "   "  << graph1->GetErrorY(a1) << "    " << graph2->GetErrorY(b1) << endl;
        cout << "ratioErrorArray[1] = " << ratioErrorArray[1] << "  " << graph1->GetErrorX(a2) << "    " << graph2->GetErrorX(b2) << "   "  << graph1->GetErrorY(a2) << "    " << graph2->GetErrorY(b2) << endl;
        cout << "ratioErrorArray[2] = " << ratioErrorArray[2] << "  " << graph1->GetErrorX(a5) << "    " << graph2->GetErrorX(b5) << "   "  << graph1->GetErrorY(a5) << "    " << graph2->GetErrorY(b5) << endl;
        cout << "ratioErrorArray[3] = " << ratioErrorArray[3] << "  " << graph1->GetErrorX(a10) << "    " << graph2->GetErrorX(b10) << "   "  << graph1->GetErrorY(a10) << "    " << graph2->GetErrorY(b10) << endl;
        cout << "ratioErrorArray[4] = " << ratioErrorArray[4] << "  " << graph1->GetErrorX(a20) << "    " << graph2->GetErrorX(b20) << "   "  << graph1->GetErrorY(a20) << "    " << graph2->GetErrorY(b20) << endl;

        TGraphErrors* ratioGraph = new TGraphErrors(5, pArray, ratioArray, pErrorArray, ratioErrorArray);

        TGraphErrors* fgraphe = dynamic_cast<TGraphErrors*>(f1->Get("SampFvsp"));
        TGraphErrors* fgraphpi = dynamic_cast<TGraphErrors*>(f2->Get("SampFvsp"));

        TCanvas *c_ratioGraph = new TCanvas("c_ratioGraph", "c_ratioGraph", 800, 600);
        c_ratioGraph->cd();
        ratioGraph->SetTitle("Ratio of E_{e^{-}} to E_{#pi^{-}}");
        ratioGraph->GetXaxis()->SetTitle("p [GeV/c]");
        ratioGraph->GetYaxis()->SetTitle("E_{e^{-}} / E_{#pi^{-}}");
        ratioGraph->SetMarkerStyle(20);
        ratioGraph->SetMarkerSize(2);
        ratioGraph->SetLineWidth(2);
        ratioGraph->GetYaxis()->SetRangeUser(0.3, 3.0);
        ratioGraph->Draw("AP");

        TLine* line = new TLine(ratioGraph->GetXaxis()->GetXmin(), 1, ratioGraph->GetXaxis()->GetXmax(), 1);
        line->SetLineColor(kRed);
        line->SetLineWidth(2);
        line->SetLineStyle(10);
        line->Draw("SAME");

        TCanvas *c_MeanEvsp = new TCanvas("c_MeanEvsp", "c_MeanEvsp", 800, 600);
        c_MeanEvsp->cd();
        graph1->SetMarkerColor(2);
        graph1->SetMarkerSize(2);
        graph1->SetLineColor(2);
        graph1->SetLineWidth(2);
        graph2->SetMarkerColor(4);
        graph2->SetMarkerSize(2);
        graph2->SetLineColor(4);
        graph2->SetLineWidth(2);
        graph1->GetYaxis()->SetRangeUser(7e-8, 0.7);
        graph1->Draw("AP");
        graph2->Draw("SAMEP");
        graph1->SetTitle("e^{-} gun");
        graph2->SetTitle("#pi^{-} gun");
        c_MeanEvsp->BuildLegend();

        TCanvas *c_SampFvsp = new TCanvas("c_SampFvsp", "c_SampFvsp", 800, 600);
        c_SampFvsp->cd();
        fgraphe->SetMarkerColor(2);
        fgraphe->SetMarkerSize(2);
        fgraphe->SetLineColor(2);
        fgraphe->SetLineWidth(2);
        fgraphpi->SetMarkerColor(4);
        fgraphpi->SetMarkerSize(2);
        fgraphpi->SetLineColor(4);
        fgraphpi->SetLineWidth(2);
        fgraphe->GetYaxis()->SetRangeUser(0.00007, 60e-3);
        fgraphe->Draw("AP");
        fgraphpi->Draw("SAMEP");
        fgraphe->SetTitle("e^{-} gun");
        fgraphpi->SetTitle("#pi^{-} gun");
        c_SampFvsp->BuildLegend();
    
    TFile* outputFile = new TFile("output.root", "RECREATE");
    ratioGraph->SetName("g_ebypiratio");
    ratioGraph->Write();
    graph1->SetName("g_MeanEvsp_e");
    graph1->Write();
    graph2->SetName("g_MeanEvsp_pi");
    graph2->Write();
    fgraphe->SetName("g_SampFvsp_e");
    fgraphe->Write();
    fgraphpi->SetName("g_SampFvsp_pi");
    fgraphpi->Write();
    outputFile->Close();
}
