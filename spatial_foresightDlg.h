
// spatial_foresightDlg.h: 头文件
//
#include "AboutDlg.h"
#include <fstream>
#include <sstream>
#include <vector>

#define PI 3.1415926
#define rad2deg 180.0 / PI

using namespace std;

#pragma once


// CspatialforesightDlg 对话框
class CspatialforesightDlg : public CDialogEx
{
	// 构造
public:
	CspatialforesightDlg(CWnd* pParent = nullptr);	// 标准构造函数

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPATIAL_FORESIGHT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	double N1 = 0, N2 = 0;
	struct in_out_data
	{
		double X_s = 0, Y_s = 0, Z_s = 0, Phi = 0, Omega = 0, Kaba = 0, f = 0, x = 0, y = 0;
	} tmp_data;
	struct Aux_Coor
	{
		double u = 0, v = 0, w = 0;
	} tmp_aux_coor;
	struct Photo_Coor
	{
		double x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	}tmp_photo_coor;
	vector<Photo_Coor> photoCoor_vec;
	vector<in_out_data> data_vec;
	vector<Aux_Coor> aux_data_vec;
	vector<vector<double>> Trans_mat;
	vector<vector<vector<double>>> Trans_Mat_vec;
	vector<vector<double>> Trans_calc(double phi, double omega, double kaba);
	CMenu menu;

	AboutDlg dlg;

	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void FileRead();
	afx_msg void ExitFunc();
private:
	CListCtrl Listctl;
public:
	afx_msg void Calc_Auxiliary_Coordinates();
	afx_msg void Calc_Project_Fac();
	afx_msg void Calc_Photo_Coor();
	afx_msg void TestCalc();
	afx_msg void TestDataRead();
	afx_msg void AboutFunc();
};
