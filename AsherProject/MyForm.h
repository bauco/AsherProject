#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/stitching/warpers.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/features2d/features2d.hpp"

namespace AsherProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace std;
	using namespace cv;

	Mat src, src_ROI, src_gray, src_threshold, src_blur, src_detected_edges, src_erosion, src_dilation, src_contours, src_elipse;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	private: System::Windows::Forms::TrackBar^  ThresholdTrackBar;

	private: System::Windows::Forms::ComboBox^  ThresholdComboBox;
	private: System::Windows::Forms::Button^  BlurButton;
	private: System::Windows::Forms::ComboBox^  BlurComboBox;
	private: System::Windows::Forms::TrackBar^  EdgeTrresholdTrackBar;
	private: System::Windows::Forms::ComboBox^  EdgeComboBox;
	private: System::Windows::Forms::Button^  ROIButton;
	private: System::Windows::Forms::Button^  Applybutton;
	private: System::Windows::Forms::ComboBox^  ErosionComboBox;
	private: System::Windows::Forms::TrackBar^  ErosionTrackBar;
	private: System::Windows::Forms::TrackBar^  DilationTrackBar;
	private: Rectangle ROIrect = Rectangle(0, 0, 0, 0);
	private: PointF lineStart;
	private: PointF lineEnd;
	private: bool ROIdefine = false;
	private: bool ExortReady = false;
	private: System::Windows::Forms::Button^  ExportButton;
	private: System::Windows::Forms::TrackBar^  BolbMaxtrackBar;
	private: System::Windows::Forms::TrackBar^  BolbMinTrackBar;
	private: System::Windows::Forms::TrackBar^  BolbMaxAreatrackBar;




	public:

	protected:
		Bitmap^ imgSrc;
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	
	private: System::Windows::Forms::Button^  LoadImageButton;
	private: System::Windows::Forms::PictureBox^  pictureBox;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::Panel^  panel5;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Panel^  panel3;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->LoadImageButton = (gcnew System::Windows::Forms::Button());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->Applybutton = (gcnew System::Windows::Forms::Button());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->BolbMaxtrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->BolbMinTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->ExportButton = (gcnew System::Windows::Forms::Button());
			this->DilationTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->ErosionTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->ErosionComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->ROIButton = (gcnew System::Windows::Forms::Button());
			this->EdgeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->EdgeTrresholdTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->BlurComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->BlurButton = (gcnew System::Windows::Forms::Button());
			this->ThresholdComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->ThresholdTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->BolbMaxAreatrackBar = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->panel1->SuspendLayout();
			this->panel4->SuspendLayout();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BolbMaxtrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BolbMinTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DilationTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ErosionTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EdgeTrresholdTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ThresholdTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BolbMaxAreatrackBar))->BeginInit();
			this->SuspendLayout();
			// 
			// LoadImageButton
			// 
			this->LoadImageButton->Location = System::Drawing::Point(12, 12);
			this->LoadImageButton->Name = L"LoadImageButton";
			this->LoadImageButton->Size = System::Drawing::Size(118, 23);
			this->LoadImageButton->TabIndex = 0;
			this->LoadImageButton->Text = L"Load Image";
			this->LoadImageButton->UseVisualStyleBackColor = true;
			this->LoadImageButton->Click += gcnew System::EventHandler(this, &MyForm::LoadImageButton_Click);
			// 
			// pictureBox
			// 
			this->pictureBox->BackColor = System::Drawing::SystemColors::ControlDark;
			this->pictureBox->Cursor = System::Windows::Forms::Cursors::Cross;
			this->pictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox->Location = System::Drawing::Point(0, 0);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(562, 487);
			this->pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox->TabIndex = 1;
			this->pictureBox->TabStop = false;
			this->pictureBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox_MouseDown);
			this->pictureBox->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox_MouseUp);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->pictureBox);
			this->panel1->Controls->Add(this->panel4);
			this->panel1->Controls->Add(this->panel5);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(141, 24);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(643, 537);
			this->panel1->TabIndex = 2;
			// 
			// panel4
			// 
			this->panel4->Controls->Add(this->Applybutton);
			this->panel4->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel4->Location = System::Drawing::Point(0, 487);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(562, 50);
			this->panel4->TabIndex = 2;
			// 
			// Applybutton
			// 
			this->Applybutton->Enabled = false;
			this->Applybutton->Location = System::Drawing::Point(130, 15);
			this->Applybutton->Name = L"Applybutton";
			this->Applybutton->Size = System::Drawing::Size(75, 23);
			this->Applybutton->TabIndex = 0;
			this->Applybutton->Text = L"Apply";
			this->Applybutton->UseVisualStyleBackColor = true;
			this->Applybutton->Click += gcnew System::EventHandler(this, &MyForm::Applybutton_Click);
			// 
			// panel5
			// 
			this->panel5->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel5->Location = System::Drawing::Point(562, 0);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(81, 537);
			this->panel5->TabIndex = 3;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->BolbMaxAreatrackBar);
			this->panel2->Controls->Add(this->BolbMaxtrackBar);
			this->panel2->Controls->Add(this->BolbMinTrackBar);
			this->panel2->Controls->Add(this->ExportButton);
			this->panel2->Controls->Add(this->DilationTrackBar);
			this->panel2->Controls->Add(this->ErosionTrackBar);
			this->panel2->Controls->Add(this->ErosionComboBox);
			this->panel2->Controls->Add(this->ROIButton);
			this->panel2->Controls->Add(this->EdgeComboBox);
			this->panel2->Controls->Add(this->EdgeTrresholdTrackBar);
			this->panel2->Controls->Add(this->BlurComboBox);
			this->panel2->Controls->Add(this->BlurButton);
			this->panel2->Controls->Add(this->ThresholdComboBox);
			this->panel2->Controls->Add(this->ThresholdTrackBar);
			this->panel2->Controls->Add(this->LoadImageButton);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel2->Location = System::Drawing::Point(0, 24);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(141, 537);
			this->panel2->TabIndex = 3;
			// 
			// BolbMaxtrackBar
			// 
			this->BolbMaxtrackBar->Location = System::Drawing::Point(12, 416);
			this->BolbMaxtrackBar->Maximum = 220;
			this->BolbMaxtrackBar->Name = L"BolbMaxtrackBar";
			this->BolbMaxtrackBar->Size = System::Drawing::Size(118, 45);
			this->BolbMaxtrackBar->TabIndex = 16;
			this->BolbMaxtrackBar->Value = 220;
			// 
			// BolbMinTrackBar
			// 
			this->BolbMinTrackBar->Location = System::Drawing::Point(12, 376);
			this->BolbMinTrackBar->Maximum = 220;
			this->BolbMinTrackBar->Minimum = 1;
			this->BolbMinTrackBar->Name = L"BolbMinTrackBar";
			this->BolbMinTrackBar->Size = System::Drawing::Size(123, 45);
			this->BolbMinTrackBar->TabIndex = 15;
			this->BolbMinTrackBar->Value = 50;
			// 
			// ExportButton
			// 
			this->ExportButton->Location = System::Drawing::Point(12, 347);
			this->ExportButton->Name = L"ExportButton";
			this->ExportButton->Size = System::Drawing::Size(118, 23);
			this->ExportButton->TabIndex = 14;
			this->ExportButton->Text = L"Export Contors";
			this->ExportButton->UseVisualStyleBackColor = true;
			this->ExportButton->Click += gcnew System::EventHandler(this, &MyForm::ExportButton_Click);
			// 
			// DilationTrackBar
			// 
			this->DilationTrackBar->Enabled = false;
			this->DilationTrackBar->Location = System::Drawing::Point(12, 308);
			this->DilationTrackBar->Maximum = 21;
			this->DilationTrackBar->Name = L"DilationTrackBar";
			this->DilationTrackBar->Size = System::Drawing::Size(123, 45);
			this->DilationTrackBar->TabIndex = 13;
			this->DilationTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::DilationTrackBar_Scroll);
			// 
			// ErosionTrackBar
			// 
			this->ErosionTrackBar->Enabled = false;
			this->ErosionTrackBar->Location = System::Drawing::Point(12, 274);
			this->ErosionTrackBar->Maximum = 21;
			this->ErosionTrackBar->Name = L"ErosionTrackBar";
			this->ErosionTrackBar->Size = System::Drawing::Size(123, 45);
			this->ErosionTrackBar->TabIndex = 12;
			this->ErosionTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::ErosionTrackBar_Scroll);
			// 
			// ErosionComboBox
			// 
			this->ErosionComboBox->FormattingEnabled = true;
			this->ErosionComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"MORPH_RECT", L"MORPH_CROSS", L"MORPH_ELLIPSE" });
			this->ErosionComboBox->Location = System::Drawing::Point(12, 247);
			this->ErosionComboBox->Name = L"ErosionComboBox";
			this->ErosionComboBox->Size = System::Drawing::Size(123, 21);
			this->ErosionComboBox->TabIndex = 11;
			this->ErosionComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::ErosionComboBox_SelectedIndexChanged);
			// 
			// ROIButton
			// 
			this->ROIButton->Enabled = false;
			this->ROIButton->Location = System::Drawing::Point(12, 41);
			this->ROIButton->Name = L"ROIButton";
			this->ROIButton->Size = System::Drawing::Size(118, 23);
			this->ROIButton->TabIndex = 10;
			this->ROIButton->Text = L"region of interest";
			this->ROIButton->UseVisualStyleBackColor = true;
			this->ROIButton->Click += gcnew System::EventHandler(this, &MyForm::ROIButton_Click);
			// 
			// EdgeComboBox
			// 
			this->EdgeComboBox->FormattingEnabled = true;
			this->EdgeComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Canny Edge Detector", L"Sobel Derivatives" });
			this->EdgeComboBox->Location = System::Drawing::Point(12, 182);
			this->EdgeComboBox->Name = L"EdgeComboBox";
			this->EdgeComboBox->Size = System::Drawing::Size(123, 21);
			this->EdgeComboBox->TabIndex = 9;
			this->EdgeComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::EdgeComboBox_SelectedIndexChanged);
			// 
			// EdgeTrresholdTrackBar
			// 
			this->EdgeTrresholdTrackBar->Enabled = false;
			this->EdgeTrresholdTrackBar->Location = System::Drawing::Point(12, 213);
			this->EdgeTrresholdTrackBar->Maximum = 100;
			this->EdgeTrresholdTrackBar->Name = L"EdgeTrresholdTrackBar";
			this->EdgeTrresholdTrackBar->Size = System::Drawing::Size(118, 45);
			this->EdgeTrresholdTrackBar->TabIndex = 8;
			this->EdgeTrresholdTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::EdgeTrresholdTrackBar_Scroll);
			// 
			// BlurComboBox
			// 
			this->BlurComboBox->FormattingEnabled = true;
			this->BlurComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Original", L"Blur", L"Gaussian Blur", L"Median Blur",
					L"Bilateral Filter"
			});
			this->BlurComboBox->Location = System::Drawing::Point(12, 130);
			this->BlurComboBox->Name = L"BlurComboBox";
			this->BlurComboBox->Size = System::Drawing::Size(118, 21);
			this->BlurComboBox->TabIndex = 7;
			this->BlurComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::BlurComboBox_SelectedIndexChanged);
			// 
			// BlurButton
			// 
			this->BlurButton->Enabled = false;
			this->BlurButton->Location = System::Drawing::Point(12, 157);
			this->BlurButton->Name = L"BlurButton";
			this->BlurButton->Size = System::Drawing::Size(118, 23);
			this->BlurButton->TabIndex = 6;
			this->BlurButton->Text = L"Blur";
			this->BlurButton->UseVisualStyleBackColor = true;
			this->BlurButton->Click += gcnew System::EventHandler(this, &MyForm::BlurButton_Click);
			// 
			// ThresholdComboBox
			// 
			this->ThresholdComboBox->Enabled = false;
			this->ThresholdComboBox->FormattingEnabled = true;
			this->ThresholdComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Binary", L"Binary Inverted", L"Threshold Truncated",
					L"Threshold to Zero", L"Threshold to Zero Inverted"
			});
			this->ThresholdComboBox->Location = System::Drawing::Point(12, 70);
			this->ThresholdComboBox->Name = L"ThresholdComboBox";
			this->ThresholdComboBox->Size = System::Drawing::Size(118, 21);
			this->ThresholdComboBox->TabIndex = 5;
			this->ThresholdComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::ThresholdComboBox_SelectedIndexChanged);
			// 
			// ThresholdTrackBar
			// 
			this->ThresholdTrackBar->Enabled = false;
			this->ThresholdTrackBar->Location = System::Drawing::Point(12, 97);
			this->ThresholdTrackBar->Maximum = 255;
			this->ThresholdTrackBar->Name = L"ThresholdTrackBar";
			this->ThresholdTrackBar->Size = System::Drawing::Size(118, 45);
			this->ThresholdTrackBar->TabIndex = 4;
			this->ThresholdTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::ThresholdTrackBar_Scroll);
			// 
			// panel3
			// 
			this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel3->Location = System::Drawing::Point(0, 0);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(784, 24);
			this->panel3->TabIndex = 4;
			// 
			// BolbMaxAreatrackBar
			// 
			this->BolbMaxAreatrackBar->Location = System::Drawing::Point(22, 455);
			this->BolbMaxAreatrackBar->Maximum = 1000;
			this->BolbMaxAreatrackBar->Name = L"BolbMaxAreatrackBar";
			this->BolbMaxAreatrackBar->Size = System::Drawing::Size(104, 45);
			this->BolbMaxAreatrackBar->TabIndex = 17;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel3);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel4->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BolbMaxtrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BolbMinTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DilationTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ErosionTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EdgeTrresholdTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ThresholdTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BolbMaxAreatrackBar))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

private: Void LoadImageButton_Click(Object^  sender, EventArgs^  e) {
		OpenFileDialog^ dirOpen = gcnew OpenFileDialog();
		dirOpen->Filter = "Image(*.bmp; *.jpg)|[*.bmp; *.jpg|All files (*.*)|*.*||";
		if (dirOpen->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}
		imgSrc = gcnew Bitmap(dirOpen->FileName);
		if (imgSrc->Width < imgSrc->Height)
		{
			imgSrc = rotateTextureGrid(imgSrc);
		}

		pictureBox->Image = imgSrc;
		pictureBox->Refresh();
		src = BitmapToMat();
		//imshow("Source image showing via OpenCv", src);
		//namedWindow("Source image showing via OpenCv", WINDOW_NORMAL);
		//cv::resizeWindow("Source image showing via OpenCv", 800, 600);
		ROIButton->Enabled = true;
	}
private: Bitmap^ rotateTextureGrid(Bitmap^ _currentPicture)
	{
		Bitmap^ ret = gcnew Bitmap(_currentPicture->Height, _currentPicture->Width);      //reminder we are flipping these in the target
				 
		for (int y = 0; y < _currentPicture->Height; y++)
		{
			for (int x = 0; x < _currentPicture->Width; x++)
			{
				ret->SetPixel(y, (_currentPicture->Width - 1 - x),_currentPicture->GetPixel(x, y));         //juggle the pixels around
			}
		}

		return ret;
	}
	
private: System::Void Applybutton_Click(System::Object^  sender, System::EventArgs^  e) {
	if (ROIdefine)
	{
		cv::Size s = src.size();
		
		double wfactor = (double)s.width / pictureBox->Width;
		double hfactor = (double)s.height / pictureBox->Height;

		src_ROI = src(Rect(ROIrect.X * wfactor, ROIrect.Y * hfactor,ROIrect.Width * wfactor, ROIrect.Height * hfactor));
		ROIdefine = false;
		System::Drawing::Graphics^ graphics = pictureBox->CreateGraphics();
		System::IntPtr ptr(src_ROI.ptr());
		pictureBox->Image = gcnew System::Drawing::Bitmap(src_ROI.cols, src_ROI.rows, src_ROI.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr);
		pictureBox->Refresh();
		Applybutton->Enabled = false;
	}
	else if (ExortReady)
	{
		ExortReady = false;
		
		int thickness = 5;
		int lineType = LINE_8;
		cv::Size s = src_elipse.size();

		double wfactor = (double)s.width / pictureBox->Width;
		double hfactor = (double)s.height / pictureBox->Height;

		cv::Point p(lineStart.X * wfactor, lineStart.Y * hfactor);
		cv::Point p2(lineEnd.X * wfactor, lineEnd.Y * hfactor);
		line(src_elipse, p, p2, Scalar(255, 0, 0), thickness, lineType);
		imshow("d", src_elipse);
		pictureBox->Refresh();
		Applybutton->Enabled = false;
	}
	else
	{
		pictureBox->Refresh();
		Applybutton->Enabled = false;
	}
	src_gray = BitmapToMat();
}

private: Mat BitmapToMat()
	{
		System::Drawing::Bitmap^ bitmap = (Bitmap^) pictureBox->Image;
		IplImage* tmp;

		System::Drawing::Imaging::BitmapData^ bmData = bitmap->LockBits(System::Drawing::Rectangle(0, 0, bitmap->Width, bitmap->Height), System::Drawing::Imaging::ImageLockMode::ReadWrite, bitmap->PixelFormat);
		if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format8bppIndexed)
		{
			tmp = cvCreateImage(cvSize(bitmap->Width, bitmap->Height), IPL_DEPTH_8U, 1);
			tmp->imageData = (char*)bmData->Scan0.ToPointer();
		}

		else if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format24bppRgb)
		{

			tmp = cvCreateImage(cvSize(bitmap->Width, bitmap->Height), IPL_DEPTH_8U, 3);
			tmp->imageData = (char*)bmData->Scan0.ToPointer();
		}

		bitmap->UnlockBits(bmData);

		return cvarrToMat(tmp);
	}
private: void ConvertMatToBitmap(Mat matToConvert)
	{
		System::Drawing::Graphics^ graphics = pictureBox->CreateGraphics();
		System::IntPtr ptr(matToConvert.ptr());
		if (matToConvert.channels() == 3)
		{
			pictureBox->Image = gcnew System::Drawing::Bitmap(matToConvert.cols, matToConvert.rows,  matToConvert.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb,
				ptr);
		}
		else
		{
			pictureBox->Image = gcnew System::Drawing::Bitmap(matToConvert.cols, matToConvert.rows, matToConvert.step, System::Drawing::Imaging::PixelFormat::Format8bppIndexed,
				ptr);
		}
		pictureBox->Refresh();
		GC::Collect();
	}
/*	int H_MIN = 0;
	int H_MAX = 256;
	int S_MIN = 0;
	int S_MAX = 256;
	int V_MIN = 0;
	int V_MAX = 256;*/

private: Void ROIButton_Click(Object^  sender, EventArgs^  e) {
		
		//CruserpictureBox->Visible = true;
		ROIdefine = true;

		//delete myBrush;
		//delete formGraphics;
		// Set the Current cursor, move the cursor's Position,
		// and set its clipping rectangle to the form.
		//ConvertMatToBitmap(src);
		//Rect2d r = selectROI(src);
		//src_ROI = src(r);
		//imshow("Source image showing via OpenCv", src_ROI);
		//src_ROI.copyTo( src);
		ThresholdComboBox->Enabled = true;
	}
private: System::Void pictureBox_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (ROIdefine)
	{
		ROIrect.Location = e->Location;
		ROIrect.X = e->X;
		ROIrect.Y = e->Y;
	}
	else if (ExortReady)
	{
		lineStart.X = e->X;
		lineStart.Y = e->Y;
	}
}
private: System::Void pictureBox_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (ROIdefine)
	{
		pictureBox->Refresh();
		ROIrect.Height = e->Y - ROIrect.Y;
		ROIrect.Width = e->X - ROIrect.X;
		System::Drawing::Pen^ myBrush = gcnew System::Drawing::Pen(System::Drawing::Color::Red);
		System::Drawing::Graphics^ formGraphics;
		formGraphics = pictureBox->CreateGraphics();
		formGraphics->DrawRectangle(myBrush, ROIrect);
		Applybutton->Enabled = true;
	}
	else if (ExortReady)
	{
		pictureBox->Refresh();
		lineEnd.X = e->X;
		lineEnd.Y = e->Y;
		System::Drawing::Pen^ myBrush = gcnew System::Drawing::Pen(System::Drawing::Color::Red);
		System::Drawing::Graphics^ formGraphics;
		formGraphics = pictureBox->CreateGraphics();
		formGraphics->DrawLine(myBrush, lineStart, lineEnd);
		Applybutton->Enabled = true;
	}
}
	
private: Void ThresholdComboBox_SelectedIndexChanged(Object^  sender, EventArgs^  e) {
		ThresholdTrackBar->Enabled = true;
	}
private: Void ThresholdTrackBar_Scroll(Object^  sender, EventArgs^  e) {
		/* 0: Binary
		1: Binary Inverted
		2: Threshold Truncated
		3: Threshold to Zero
		4: Threshold to Zero Inverted */

		cvtColor(src_ROI, src_gray, CV_BGR2GRAY);
		threshold(src_gray, src_threshold, ThresholdTrackBar->Value, 255, ThresholdComboBox->SelectedIndex);
		ConvertMatToBitmap(src_threshold);
		Applybutton->Enabled = true;
	}

private: Void BlurButton_Click(Object^  sender, EventArgs^  e) {
		int DELAY_CAPTION = 1500;
		int DELAY_BLUR = 100;
		int MAX_KERNEL_LENGTH = 31;
		src_blur = src_gray.clone();
		/*	0 = Original
		1 = Blur
		2 = Gaussian Blur
		3 = Median Blur
		4 = Bilateral Filter*/
		switch (BlurComboBox->SelectedIndex)
		{
		case(0):
		{
			src_blur = src_gray;
			break;
		}
		case(1):
		{
			for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
			{
				blur(src_gray, src_blur, cv::Size(i, i), cv::Point(-1, -1));
				if (display_dst(DELAY_BLUR) != 0)
				{
					break;
				}
			}
		}
		case(2):
		{
			for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
			{
				GaussianBlur(src_gray, src_blur, cv::Size(i, i), 0, 0);
				if (display_dst(DELAY_BLUR) != 0)
				{
					break;
				}
			}
			break;
		}
		case(3):
		{
			for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
			{
				medianBlur(src_gray, src_blur, i);
				if (display_dst(DELAY_BLUR) != 0)
				{
					break;
				}
			}
			break;
		}
		case(4):
		{
			for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
			{
				bilateralFilter(src_gray, src_blur, i, i * 2, i / 2);
				if (display_dst(DELAY_BLUR) != 0)
				{
					break;
				}
			}
			break;
		}
		default:
		{
			break;
		}
		//imshow("Source image showing via OpenCv", src_blur);
		ConvertMatToBitmap(src_blur);
		Applybutton->Enabled = true;
		}
	}
private: Void BlurComboBox_SelectedIndexChanged(Object^  sender, EventArgs^  e) {
		BlurButton->Enabled = true;
	}
private: int display_dst(int delay)
	{
		int c = waitKey(delay);
		if (c >= 0) { return -1; }
		return 0;
	}

private: Void EdgeComboBox_SelectedIndexChanged(Object^  sender, EventArgs^  e) {
		/*	0 = Canny Edge Detector
		1 = Sobel Derivatives
		*/
		switch (EdgeComboBox->SelectedIndex)
		{
			case(0):
			{
				EdgeTrresholdTrackBar->Enabled = true;
				int edgeThresh = 1;
				int ratio = 3;
				int kernel_size = 3;

				Canny(src_gray, src_detected_edges, EdgeTrresholdTrackBar->Value, EdgeTrresholdTrackBar->Value*ratio, kernel_size);

				/// Using Canny's output as a mask, we display our result
				break;
			}
			case(1):
			{
				EdgeTrresholdTrackBar->Enabled = false;
				int scale = 1;
				int delta = 0;
				int ddepth = CV_16S;
				Mat grad_x, grad_y;
				Mat abs_grad_x, abs_grad_y;

				/// Gradient X
				//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
				Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
				convertScaleAbs(grad_x, abs_grad_x);

				/// Gradient Y
				//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
				Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
				convertScaleAbs(grad_y, abs_grad_y);

				/// Total Gradient (approximate)
				addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, src_detected_edges);
				break;
			}
		}
		//imshow("Source image showing via OpenCv", src_detected_edges);
		ConvertMatToBitmap(src_detected_edges);

	}
private: Void EdgeTrresholdTrackBar_Scroll(Object^  sender, EventArgs^  e) {
		if (EdgeComboBox->SelectedIndex == 0)
		{
			int edgeThresh = 1;
			int ratio = 3;
			int kernel_size = 3;

			Canny(src_gray, src_detected_edges, EdgeTrresholdTrackBar->Value, EdgeTrresholdTrackBar->Value*ratio, kernel_size);
			//imshow("Source image showing via OpenCv", src_detected_edges);
			ConvertMatToBitmap(src_detected_edges);

			// Using Canny's output as a mask, we display our result
		}
		Applybutton->Enabled = true;
	}


private: System::Void ErosionComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	ErosionTrackBar->Enabled = true;
	DilationTrackBar->Enabled = true;
}
private: System::Void ErosionTrackBar_Scroll(System::Object^  sender, System::EventArgs^  e) 
{
	int erosion_type = ErosionComboBox->SelectedIndex;

	Mat element = getStructuringElement(erosion_type, cv::Size(2 * ErosionTrackBar->Value + 1, 2 * ErosionTrackBar->Value + 1), cv::Point(ErosionTrackBar->Value, ErosionTrackBar->Value));

	/// Apply the erosion operation
	erode(src_gray, src_erosion, element);
	ConvertMatToBitmap(src_erosion);
	Applybutton->Enabled = true;
}
private: System::Void DilationTrackBar_Scroll(System::Object^  sender, System::EventArgs^  e)
{
	int erosion_type = ErosionComboBox->SelectedIndex;
	Mat element = getStructuringElement(erosion_type, cv::Size(2 * DilationTrackBar->Value + 1, 2 * DilationTrackBar->Value + 1), cv::Point(DilationTrackBar->Value, DilationTrackBar->Value));
	/// Apply the dilation operation
	dilate(src_gray, src_dilation, element);
	ConvertMatToBitmap(src_dilation);
	Applybutton->Enabled = true;
}
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	if (ROIdefine)
	{
	}
}

private: System::Void ExportButton_Click(System::Object^  sender, System::EventArgs^  e) {
	RNG rng(12345);
	vector < vector < cv::Point > > contours;

	vector<Vec4i> hierarchy;
	Canny(src_gray, src_threshold, EdgeTrresholdTrackBar->Value, EdgeTrresholdTrackBar->Value * 2, 3);

	findContours(src_threshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	cv::SimpleBlobDetector::Params BolbParmas;
	// Change thresholds
	BolbParmas.minThreshold = BolbMinTrackBar->Value;
	BolbParmas.maxThreshold = BolbMaxtrackBar->Value;
	BolbParmas.filterByArea = true;
	BolbParmas.minArea = BolbMaxAreatrackBar->Value;
	cv::Ptr<SimpleBlobDetector> bolbDetector = cv::SimpleBlobDetector::create(BolbParmas);
	std::vector<KeyPoint> keypoints;
	bolbDetector->detect(src_threshold, keypoints);

	// Draw detected blobs as red circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
	Mat im_with_keypoints;
	drawKeypoints(src_threshold, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// Show blobs
	imshow("keypoints", im_with_keypoints);
	/// Draw contours
	src_contours = Mat::zeros(src_threshold.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(src_contours, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
	}

	src_elipse = Mat::zeros(src_threshold.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++)
	{
		size_t count = contours[i].size();
		if (count < 6)
			continue;
		Mat pointsf;
		Mat(contours[i]).convertTo(pointsf, CV_32F);
		RotatedRect box = fitEllipse(pointsf);
		if (MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height) * 30)
			continue;
		drawContours(src_elipse, contours, (int)i, Scalar::all(255), 1, 8);
		ellipse(src_elipse, box, Scalar(0, 0, 255), 1, LINE_AA);
		ellipse(src_elipse, box.center, box.size*0.5f, box.angle, 0, 360, Scalar(0, 255, 255), 1, LINE_AA);
		Point2f vtx[4];
		box.points(vtx);
		line(src_elipse, (vtx[0] + vtx[1])* 0.5  , (vtx[2] + vtx[3]) * 0.5, Scalar(0, 255, 0), 1, LINE_AA);
	}

	ConvertMatToBitmap(src_elipse);
	ExortReady = true;
	/// Show in a window
	// Setup SimpleBlobDetector parameters.

}

};
}
