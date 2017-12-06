#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/stitching/warpers.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/features2d/features2d.hpp"

bool compareContourAreas(std::vector<cv::Point> contour1, std::vector<cv::Point> contour2) {
	double i = fabs(contourArea(cv::Mat(contour1)));
	double j = fabs(contourArea(cv::Mat(contour2)));
	return (i < j);
}

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

	
	Mat src, src_ROI, src_gray, src_threshold, src_tranform, src_detected_edges, src_erosion, src_dilation, src_contours, src_elipse;
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
	private: System::Windows::Forms::ComboBox^  ContursComboBox;
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
	
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;

	// panels to save ratios
	private: System::Windows::Forms::Panel^  TopPanel;
	private: System::Windows::Forms::Panel^  PictureBoxPanel;
	private: System::Windows::Forms::Panel^  ButtomMidlePanel;
	private: System::Windows::Forms::Panel^  RightMidlePanelNOUSE;
	private: System::Windows::Forms::Panel^  LeftMidleFunctionsPanel;

	private: System::Windows::Forms::PictureBox^  pictureBox;

	//ButtomMidlePanel Buttons:
	private: System::Windows::Forms::Button^  UndoButton;
	private: System::Windows::Forms::Button^  Applybutton;

	//LeftMidleFunctionsPanel buttons:
	private: System::Windows::Forms::Button^  LoadImageButton;
	private: System::Windows::Forms::Button^  ROIButton;
	private: System::Windows::Forms::Button^  ExportButton;

	//ButtomMidlePanel ComboBoxs:
	private: System::Windows::Forms::ComboBox^  ThresholdComboBox;
	private: System::Windows::Forms::ComboBox^  ErosionComboBox;
	private: System::Windows::Forms::ComboBox^  TransformationscomboBox;

	//ButtomMidlePanel TrackBars:
	private: System::Windows::Forms::TrackBar^  ThresholdTrackBar;
	private: System::Windows::Forms::TrackBar^  ErosionTrackBar;
	private: System::Windows::Forms::TrackBar^  DilationTrackBar;
	private: System::Windows::Forms::TrackBar^  TransformationstrackBar;
/*
	private: System::Windows::Forms::TrackBar^  BolbMaxtrackBar;
	private: System::Windows::Forms::TrackBar^  BolbMinTrackBar;
	private: System::Windows::Forms::TrackBar^  BolbMaxAreatrackBar;
*/
	//flags for postions in progress diffrent use for the same var?
	private: bool ExortReady = false;
	private: bool ROIdefine = false;

	// rect to output  on screen -> user choicse: 1. he click the ROI Button and ROIdefine == true 
												//2. on picturebox user click and drag to create a rectangle of hes ROI 
												//3. whenuser click aplly button ROUrect location is helping to extract and create cv::Mat -> ROI
	private: Rectangle ROIrect = Rectangle(0, 0, 0, 0);
	//user line input helpers 
	//private: PointF lineStart;
	//private: PointF lineEnd;

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
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->PictureBoxPanel = (gcnew System::Windows::Forms::Panel());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->ButtomMidlePanel = (gcnew System::Windows::Forms::Panel());
			this->UndoButton = (gcnew System::Windows::Forms::Button());
			this->Applybutton = (gcnew System::Windows::Forms::Button());
			this->RightMidlePanelNOUSE = (gcnew System::Windows::Forms::Panel());
			this->LeftMidleFunctionsPanel = (gcnew System::Windows::Forms::Panel());
			this->ContursComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->ExportButton = (gcnew System::Windows::Forms::Button());
			this->ErosionComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->LoadImageButton = (gcnew System::Windows::Forms::Button());
			this->ThresholdTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->ROIButton = (gcnew System::Windows::Forms::Button());
			this->ThresholdComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TransformationscomboBox = (gcnew System::Windows::Forms::ComboBox());
			this->TransformationstrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->DilationTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->ErosionTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->TopPanel = (gcnew System::Windows::Forms::Panel());
			this->PictureBoxPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->ButtomMidlePanel->SuspendLayout();
			this->LeftMidleFunctionsPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ThresholdTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TransformationstrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DilationTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ErosionTrackBar))->BeginInit();
			this->SuspendLayout();
			// 
			// PictureBoxPanel
			// 
			this->PictureBoxPanel->Controls->Add(this->pictureBox);
			this->PictureBoxPanel->Controls->Add(this->ButtomMidlePanel);
			this->PictureBoxPanel->Controls->Add(this->RightMidlePanelNOUSE);
			this->PictureBoxPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PictureBoxPanel->Location = System::Drawing::Point(141, 24);
			this->PictureBoxPanel->Name = L"PictureBoxPanel";
			this->PictureBoxPanel->Size = System::Drawing::Size(643, 537);
			this->PictureBoxPanel->TabIndex = 2;
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
			// ButtomMidlePanel
			// 
			this->ButtomMidlePanel->Controls->Add(this->UndoButton);
			this->ButtomMidlePanel->Controls->Add(this->Applybutton);
			this->ButtomMidlePanel->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->ButtomMidlePanel->Location = System::Drawing::Point(0, 487);
			this->ButtomMidlePanel->Name = L"ButtomMidlePanel";
			this->ButtomMidlePanel->Size = System::Drawing::Size(562, 50);
			this->ButtomMidlePanel->TabIndex = 2;
			// 
			// UndoButton
			// 
			this->UndoButton->Enabled = false;
			this->UndoButton->Location = System::Drawing::Point(358, 15);
			this->UndoButton->Name = L"UndoButton";
			this->UndoButton->Size = System::Drawing::Size(75, 23);
			this->UndoButton->TabIndex = 1;
			this->UndoButton->Text = L"Undo";
			this->UndoButton->UseVisualStyleBackColor = true;
			this->UndoButton->Click += gcnew System::EventHandler(this, &MyForm::UndoButton_Click);
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
			// RightMidlePanelNOUSE
			// 
			this->RightMidlePanelNOUSE->Dock = System::Windows::Forms::DockStyle::Right;
			this->RightMidlePanelNOUSE->Location = System::Drawing::Point(562, 0);
			this->RightMidlePanelNOUSE->Name = L"RightMidlePanelNOUSE";
			this->RightMidlePanelNOUSE->Size = System::Drawing::Size(81, 537);
			this->RightMidlePanelNOUSE->TabIndex = 3;
			// 
			// LeftMidleFunctionsPanel
			// 
			this->LeftMidleFunctionsPanel->Controls->Add(this->ContursComboBox);
			this->LeftMidleFunctionsPanel->Controls->Add(this->ExportButton);
			this->LeftMidleFunctionsPanel->Controls->Add(this->ErosionComboBox);
			this->LeftMidleFunctionsPanel->Controls->Add(this->LoadImageButton);
			this->LeftMidleFunctionsPanel->Controls->Add(this->ThresholdTrackBar);
			this->LeftMidleFunctionsPanel->Controls->Add(this->ROIButton);
			this->LeftMidleFunctionsPanel->Controls->Add(this->ThresholdComboBox);
			this->LeftMidleFunctionsPanel->Controls->Add(this->TransformationscomboBox);
			this->LeftMidleFunctionsPanel->Controls->Add(this->TransformationstrackBar);
			this->LeftMidleFunctionsPanel->Controls->Add(this->DilationTrackBar);
			this->LeftMidleFunctionsPanel->Controls->Add(this->ErosionTrackBar);
			this->LeftMidleFunctionsPanel->Dock = System::Windows::Forms::DockStyle::Left;
			this->LeftMidleFunctionsPanel->Location = System::Drawing::Point(0, 24);
			this->LeftMidleFunctionsPanel->Name = L"LeftMidleFunctionsPanel";
			this->LeftMidleFunctionsPanel->Size = System::Drawing::Size(141, 537);
			this->LeftMidleFunctionsPanel->TabIndex = 3;
			// 
			// ContursComboBox
			// 
			this->ContursComboBox->Enabled = false;
			this->ContursComboBox->FormattingEnabled = true;
			this->ContursComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"All" });
			this->ContursComboBox->Location = System::Drawing::Point(12, 314);
			this->ContursComboBox->Name = L"ContursComboBox";
			this->ContursComboBox->Size = System::Drawing::Size(118, 21);
			this->ContursComboBox->TabIndex = 15;
			this->ContursComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::ContursComboBox_SelectedIndexChanged);
			// 
			// ExportButton
			// 
			this->ExportButton->Enabled = false;
			this->ExportButton->Location = System::Drawing::Point(12, 285);
			this->ExportButton->Name = L"ExportButton";
			this->ExportButton->Size = System::Drawing::Size(118, 23);
			this->ExportButton->TabIndex = 14;
			this->ExportButton->Text = L"Export Contors";
			this->ExportButton->UseVisualStyleBackColor = true;
			this->ExportButton->Click += gcnew System::EventHandler(this, &MyForm::ExportButton_Click);
			// 
			// ErosionComboBox
			// 
			this->ErosionComboBox->Enabled = false;
			this->ErosionComboBox->FormattingEnabled = true;
			this->ErosionComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"MORPH_RECT", L"MORPH_CROSS", L"MORPH_ELLIPSE" });
			this->ErosionComboBox->Location = System::Drawing::Point(12, 131);
			this->ErosionComboBox->Name = L"ErosionComboBox";
			this->ErosionComboBox->Size = System::Drawing::Size(118, 21);
			this->ErosionComboBox->TabIndex = 11;
			this->ErosionComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::ErosionComboBox_SelectedIndexChanged);
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
			// TransformationscomboBox
			// 
			this->TransformationscomboBox->Enabled = false;
			this->TransformationscomboBox->FormattingEnabled = true;
			this->TransformationscomboBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Opening", L"Closing", L"Gradient",
					L"Top Hat", L"Black Hat"
			});
			this->TransformationscomboBox->Location = System::Drawing::Point(12, 227);
			this->TransformationscomboBox->Name = L"TransformationscomboBox";
			this->TransformationscomboBox->Size = System::Drawing::Size(118, 21);
			this->TransformationscomboBox->TabIndex = 4;
			this->TransformationscomboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::TransformationscomboBox_SelectedIndexChanged);
			// 
			// TransformationstrackBar
			// 
			this->TransformationstrackBar->Enabled = false;
			this->TransformationstrackBar->Location = System::Drawing::Point(12, 254);
			this->TransformationstrackBar->Maximum = 21;
			this->TransformationstrackBar->Name = L"TransformationstrackBar";
			this->TransformationstrackBar->Size = System::Drawing::Size(118, 45);
			this->TransformationstrackBar->TabIndex = 4;
			this->TransformationstrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::TransformationstrackBar_Scroll);
			// 
			// DilationTrackBar
			// 
			this->DilationTrackBar->Enabled = false;
			this->DilationTrackBar->Location = System::Drawing::Point(12, 192);
			this->DilationTrackBar->Maximum = 21;
			this->DilationTrackBar->Name = L"DilationTrackBar";
			this->DilationTrackBar->Size = System::Drawing::Size(118, 45);
			this->DilationTrackBar->TabIndex = 13;
			this->DilationTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::DilationTrackBar_Scroll);
			// 
			// ErosionTrackBar
			// 
			this->ErosionTrackBar->Enabled = false;
			this->ErosionTrackBar->Location = System::Drawing::Point(12, 158);
			this->ErosionTrackBar->Maximum = 21;
			this->ErosionTrackBar->Name = L"ErosionTrackBar";
			this->ErosionTrackBar->Size = System::Drawing::Size(118, 45);
			this->ErosionTrackBar->TabIndex = 12;
			this->ErosionTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::ErosionTrackBar_Scroll);
			// 
			// TopPanel
			// 
			this->TopPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->TopPanel->Location = System::Drawing::Point(0, 0);
			this->TopPanel->Name = L"TopPanel";
			this->TopPanel->Size = System::Drawing::Size(784, 24);
			this->TopPanel->TabIndex = 4;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->PictureBoxPanel);
			this->Controls->Add(this->LeftMidleFunctionsPanel);
			this->Controls->Add(this->TopPanel);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->PictureBoxPanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->ButtomMidlePanel->ResumeLayout(false);
			this->LeftMidleFunctionsPanel->ResumeLayout(false);
			this->LeftMidleFunctionsPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ThresholdTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TransformationstrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DilationTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ErosionTrackBar))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
//Opens DialogBox for user to load image file bmp/jpg/all
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
		src_gray = src;
		ROIButton->Enabled = true;
	}
//help function to rotate image in case which width is shorter then hight
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

//Apply current state of image in form to mat --> src_gray
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
		ThresholdComboBox->Enabled = true;
		Applybutton->Enabled = false;
		UndoButton->Enabled = false;

	}
/*
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
		UndoButton->Enabled = false;
	}
*/
	else
	{
		pictureBox->Refresh();
		Applybutton->Enabled = false;
		UndoButton->Enabled = false;
	}
	src_gray = BitmapToMat();
}
//Apply current src_gray to screen -->picturebox
private: System::Void UndoButton_Click(System::Object^  sender, System::EventArgs^  e) {
	ConvertMatToBitmap(src_gray);
	UndoButton->Enabled = false;
	Applybutton->Enabled = false;
}

//help functions to conver from image to mat and oppusite
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
		pictureBox->Refresh();
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

//On ROI Button click a listner on picturebox is enaible --> user can click and drag to choose ROI and click apply for changes 
private: Void ROIButton_Click(Object^  sender, EventArgs^  e) {
		//CruserpictureBox->Visible = true;
		ROIdefine = true;
	}
//Picturebox listners for ROI and Export
private: System::Void pictureBox_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (ROIdefine)
	{
		ROIrect.Location = e->Location;
		ROIrect.X = e->X;
		ROIrect.Y = e->Y;
	}
/*
	else if (ExortReady)
	{
		lineStart.X = e->X;
		lineStart.Y = e->Y;
	}
*/
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
/*
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
*/
}

/** i have a bug in between the LoadImageButton_Click function to ThresholdTrackBar_Scroll function
	// At this point, the program should convert the image to binary and execute a threshold according to the option selected in ThresholdComboBox.
	// In some cases it works just fine.
	// But sometimes images are not affected by the threshold effect at all.
	// When this happens, ApllyButton.Enable == False
	// src_gray should be greyscale but in a subtle format I have not checked? Todo ***** check it ***** yaa mpager S! # ^
	// When you upload another image it can be of good use and work, but in most cases close and re-run will increase your chances of passing this step successfully.
	// ROI functions do not touch Mat objects so I think Fasher say a safe record right now.
	// 


	//TODO
	// 1. find the bug and fix it
	// 2. add morph calss info such as string ClassName,maybe some api like get/SetMorph -> contors, Draw and that shitey staff
	// 3. algae inhert morpha and impliment virtual function from morph
	// 4. but i should look for: (morph by --> contors) && Contors from imagesrc in: filterd_image object contors
		  filterd_image should have allready or can by asked at that point the morph details he look for. or some other way to by able to perfome machine learning in the future



**/

//on combobox select -> threshold scroll bar is enabled
private: Void ThresholdComboBox_SelectedIndexChanged(Object^  sender, EventArgs^  e)
{
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
		UndoButton->Enabled = true;
		ErosionComboBox->Enabled = true;
	}

//on combobox select -> erosion and dilitaion scroll bars are avilable by morph selected
private: System::Void ErosionComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	ErosionTrackBar->Enabled = true;
	DilationTrackBar->Enabled = true;
	TransformationscomboBox->Enabled = true;
	ExportButton->Enabled = true;
/*
	BolbMinTrackBar->Enabled = true;
	BolbMaxtrackBar->Enabled = true;
*/
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

//on combobox select -> transformation max and min scroll bars are avilable 
private: System::Void TransformationscomboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	TransformationstrackBar->Enabled = true;
}
private: System::Void  TransformationstrackBar_Scroll(System::Object^  sender, System::EventArgs^  e) {
	Mat element = getStructuringElement(ErosionComboBox->SelectedIndex, cv::Size(2 * TransformationstrackBar->Value + 1, 2 * TransformationstrackBar->Value + 1), cv::Point(TransformationstrackBar->Value, TransformationstrackBar->Value));
	morphologyEx(src_gray, src_tranform, TransformationscomboBox->SelectedIndex + 2, element);
	ConvertMatToBitmap(src_tranform);
	Applybutton->Enabled = true;
}

/*
private: System::Void BolbMinTrackBar_Scroll(System::Object^  sender, System::EventArgs^  e) {
	BolbRemove();
}
private: System::Void BolbMaxtrackBar_Scroll(System::Object^  sender, System::EventArgs^  e) {
	BolbRemove();
}
private: System::Void BolbRemove()
{
	RNG rng(12345);
	vector < vector < cv::Point > > contours;
	vector<Vec4i> hierarchy;
	Mat edgesrc;
	Canny(src_gray, edgesrc, BolbMinTrackBar->Value, BolbMaxtrackBar->Value, 3);
	findContours(edgesrc, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	cv::Ptr<SimpleBlobDetector> bolbDetector = cv::SimpleBlobDetector::create();
	std::vector<KeyPoint> keypoints;
	bolbDetector->detect(edgesrc, keypoints);

	src_contours = Mat::zeros(edgesrc.size(), CV_8UC3);

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
		drawContours(src_contours, contours, (int)i, Scalar::all(255), 1, 8);
	}

	ConvertMatToBitmap(src_contours);
	Applybutton->Enabled = true;
	UndoButton->Enabled = true;
}

*/
private: System::Void ExportButton_Click(System::Object^  sender, System::EventArgs^  e) {
	RNG rng(12345);
	vector < vector < cv::Point > > contours;

	vector<Vec4i> hierarchy;
	src_threshold = Mat::zeros(src_gray.size(), CV_8UC3);
	Canny(src_gray, src_threshold, ThresholdTrackBar->Value, ThresholdTrackBar->Value * 2, 3);

	findContours(src_threshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	std::sort(contours.begin(), contours.end(), compareContourAreas);
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
		Point2f vtx[4];
		box.points(vtx);
		//cross lines 
		char* str2 = (char*)(void*)Marshal::StringToHGlobalAnsi(i.ToString());
		int index = ContursComboBox->Items->IndexOf(gcnew System::String(str2));
		if (index == -1)
		{
			ContursComboBox->Items->Add(gcnew System::String( str2));
		}
		putText(src_elipse, str2, box.center, FONT_HERSHEY_PLAIN, 2, Scalar(0, 0, 255, 255));
		line(src_elipse, (vtx[0] + vtx[1])* 0.5  , (vtx[2] + vtx[3]) * 0.5, Scalar(0, 255, 0), 1, LINE_AA);
		line(src_elipse, (vtx[0] + vtx[3])* 0.5, (vtx[1] + vtx[2]) * 0.5, Scalar(0, 255, 0), 1, LINE_AA);
	}

	ConvertMatToBitmap(src_elipse);
	ExortReady = true;
	/// Show in a window
	// Setup SimpleBlobDetector parameters.
	ContursComboBox->Enabled = true;
}

private: System::Void ContursComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	if (ContursComboBox->SelectedIndex != 0)
	{
		RNG rng(12345);
		vector < vector < cv::Point > > contours;
		vector<Vec4i> hierarchy;

		src_threshold = Mat::zeros(src_gray.size(), CV_8UC3);
		Canny(src_gray, src_threshold, ThresholdTrackBar->Value, ThresholdTrackBar->Value * 2, 3);

		findContours(src_threshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
		std::sort(contours.begin(), contours.end(), compareContourAreas);
	
		Mat tmp;
		tmp = Mat::zeros(src_threshold.size(), CV_8UC3);
		size_t i = size_t::Parse(ContursComboBox->SelectedItem->ToString());
		if (i != contours.size())
		{
			Mat pointsf;
			Mat(contours[i]).convertTo(pointsf, CV_32F);
			RotatedRect box = fitEllipse(pointsf);
			drawContours(tmp, contours, (int)i, Scalar::all(255), 1, 8);
			ellipse(tmp, box, Scalar(0, 0, 255), 1, LINE_AA);
			Point2f vtx[4];
			box.points(vtx);
			//cross lines 
			line(tmp, (vtx[0] + vtx[1])* 0.5, (vtx[2] + vtx[3]) * 0.5, Scalar(0, 255, 0), 1, LINE_AA);
			line(tmp, (vtx[0] + vtx[3])* 0.5, (vtx[1] + vtx[2]) * 0.5, Scalar(0, 255, 0), 1, LINE_AA);
		}
		ConvertMatToBitmap(tmp);
	}
	else
	{
		ExportButton_Click(sender,e);
	}
}
};
}
