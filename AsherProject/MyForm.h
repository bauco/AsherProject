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

	private: System::Windows::Forms::TrackBar^  ThresholdTrackBar;

	private: System::Windows::Forms::ComboBox^  ThresholdComboBox;




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
	private: System::Windows::Forms::ComboBox^  TransformationscomboBox;
	private: System::Windows::Forms::TrackBar^  TransformationstrackBar;
	private: System::Windows::Forms::Button^  UndoButton;







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
			this->UndoButton = (gcnew System::Windows::Forms::Button());
			this->Applybutton = (gcnew System::Windows::Forms::Button());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->TransformationstrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->TransformationscomboBox = (gcnew System::Windows::Forms::ComboBox());
			this->ErosionComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->BolbMaxAreatrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->BolbMaxtrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->BolbMinTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->ExportButton = (gcnew System::Windows::Forms::Button());
			this->DilationTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->ErosionTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->ROIButton = (gcnew System::Windows::Forms::Button());
			this->ThresholdComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->ThresholdTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->panel1->SuspendLayout();
			this->panel4->SuspendLayout();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TransformationstrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BolbMaxAreatrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BolbMaxtrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BolbMinTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DilationTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ErosionTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ThresholdTrackBar))->BeginInit();
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
			this->panel4->Controls->Add(this->UndoButton);
			this->panel4->Controls->Add(this->Applybutton);
			this->panel4->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel4->Location = System::Drawing::Point(0, 487);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(562, 50);
			this->panel4->TabIndex = 2;
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
			this->panel2->Controls->Add(this->ExportButton);
			this->panel2->Controls->Add(this->BolbMinTrackBar);
			this->panel2->Controls->Add(this->BolbMaxtrackBar);
			this->panel2->Controls->Add(this->TransformationstrackBar);
			this->panel2->Controls->Add(this->TransformationscomboBox);
			this->panel2->Controls->Add(this->ErosionComboBox);
			this->panel2->Controls->Add(this->DilationTrackBar);
			this->panel2->Controls->Add(this->ErosionTrackBar);
			this->panel2->Controls->Add(this->ROIButton);
			this->panel2->Controls->Add(this->ThresholdComboBox);
			this->panel2->Controls->Add(this->ThresholdTrackBar);
			this->panel2->Controls->Add(this->LoadImageButton);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel2->Location = System::Drawing::Point(0, 24);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(141, 537);
			this->panel2->TabIndex = 3;
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
			// BolbMaxAreatrackBar
			// 
			this->BolbMaxAreatrackBar->Enabled = false;
			this->BolbMaxAreatrackBar->Location = System::Drawing::Point(12, 343);
			this->BolbMaxAreatrackBar->Maximum = 1000;
			this->BolbMaxAreatrackBar->Name = L"BolbMaxAreatrackBar";
			this->BolbMaxAreatrackBar->Size = System::Drawing::Size(118, 45);
			this->BolbMaxAreatrackBar->TabIndex = 17;
			// 
			// BolbMaxtrackBar
			// 
			this->BolbMaxtrackBar->Enabled = false;
			this->BolbMaxtrackBar->Location = System::Drawing::Point(12, 280);
			this->BolbMaxtrackBar->Maximum = 220;
			this->BolbMaxtrackBar->Name = L"BolbMaxtrackBar";
			this->BolbMaxtrackBar->Size = System::Drawing::Size(118, 45);
			this->BolbMaxtrackBar->TabIndex = 16;
			this->BolbMaxtrackBar->Value = 220;
			this->BolbMaxtrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::BolbMaxtrackBar_Scroll);
			// 
			// BolbMinTrackBar
			// 
			this->BolbMinTrackBar->Enabled = false;
			this->BolbMinTrackBar->Location = System::Drawing::Point(12, 309);
			this->BolbMinTrackBar->Maximum = 220;
			this->BolbMinTrackBar->Name = L"BolbMinTrackBar";
			this->BolbMinTrackBar->Size = System::Drawing::Size(118, 45);
			this->BolbMinTrackBar->TabIndex = 20;
			this->BolbMinTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::BolbMinTrackBar_Scroll);
			// 
			// ExportButton
			// 
			this->ExportButton->Enabled = false;
			this->ExportButton->Location = System::Drawing::Point(12, 487);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TransformationstrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BolbMaxAreatrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BolbMaxtrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BolbMinTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DilationTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ErosionTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ThresholdTrackBar))->EndInit();
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
		//imshow("Source image showing via OpenCv", src);
		//namedWindow("Source image showing via OpenCv", WINDOW_NORMAL);
		//cv::resizeWindow("Source image showing via OpenCv", 800, 600);
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
	BolbMaxtrackBar->Enabled = true;
	BolbMinTrackBar->Enabled = true;
	ExportButton->Enabled = true;
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

private: System::Void TransformationscomboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	TransformationstrackBar->Enabled = true;

}
private: System::Void  TransformationstrackBar_Scroll(System::Object^  sender, System::EventArgs^  e) {
	Mat element = getStructuringElement(ErosionComboBox->SelectedIndex, cv::Size(2 * TransformationstrackBar->Value + 1, 2 * TransformationstrackBar->Value + 1), cv::Point(TransformationstrackBar->Value, TransformationstrackBar->Value));
	morphologyEx(src_gray, src_tranform, TransformationscomboBox->SelectedIndex + 2, element);
	ConvertMatToBitmap(src_tranform);
	Applybutton->Enabled = true;
}


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
private: System::Void ExportButton_Click(System::Object^  sender, System::EventArgs^  e) {
	RNG rng(12345);
	vector < vector < cv::Point > > contours;

	vector<Vec4i> hierarchy;
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
		ellipse(src_elipse, box.center, box.size*0.5f, box.angle, 0, 360, Scalar(0, 255, 255), 1, LINE_AA);
		Point2f vtx[4];
		box.points(vtx);
		//cross lines 
		line(src_elipse, (vtx[0] + vtx[1])* 0.5  , (vtx[2] + vtx[3]) * 0.5, Scalar(0, 255, 0), 1, LINE_AA);
		line(src_elipse, (vtx[0] + vtx[3])* 0.5, (vtx[1] + vtx[2]) * 0.5, Scalar(0, 255, 0), 1, LINE_AA);

	}

	ConvertMatToBitmap(src_elipse);
	ExortReady = true;
	/// Show in a window
	// Setup SimpleBlobDetector parameters.
}

};
}
