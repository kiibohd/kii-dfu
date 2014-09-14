/* Copyright (C) 2014 by Jacob Alexander
 *
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this file.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// ----- Includes -----

// Qt
#include <QFile>
#include <QProcess>

// Local
#include <QMainWindow>



// ----- Namespaces -----

namespace Ui {
	class MainWindow;
}



// ----- Classes -----

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow( QWidget *parent = 0 );
	~MainWindow();

private slots:
	void browseFiles();
	void dfuFlashBinary();
	void dfuListDevices();
	void dfuCommandStatus();
	void dfuCommandComplete( int exitCode );

private:
	bool checkDFU( QFile *dfuUtil );

	Ui::MainWindow *ui;

	QProcess dfuUtilProcess;
	QString binaryPath;

};

#endif // MAINWINDOW_H

