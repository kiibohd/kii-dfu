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

// ----- Includes -----

// Qt
#include <QFileDialog>
#include <QScrollBar>

// Local
#include "mainwindow.h"
#include "ui_mainwindow.h"



// ----- Functions -----

MainWindow::MainWindow( QWidget *parent ) : QMainWindow( parent ), ui( new Ui::MainWindow )
{
	ui->setupUi( this );

	// Connections
	connect( ui->fileBrowseButton, SIGNAL( released() ), this, SLOT( browseFiles() ) );
	connect( ui->flashButton, SIGNAL( released() ), this, SLOT( dfuFlashBinary() ) );
	connect( ui->listDevicesButton, SIGNAL( released() ), this, SLOT( dfuListDevices() ) );
	connect( &dfuUtilProcess, SIGNAL( readyReadStandardOutput() ), this, SLOT( dfuCommandStatus() ) );
	connect( &dfuUtilProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( dfuCommandComplete( int ) ) );

	// Only use the included dfu-util
	binaryPath = QFileInfo( QCoreApplication::applicationFilePath() ).dir().absolutePath();
	dfuUtilProcess.setWorkingDirectory( binaryPath );

	// Merge the output channels
	dfuUtilProcess.setProcessChannelMode( QProcess::MergedChannels );
}

MainWindow::~MainWindow()
{
	delete ui;
}



// ----- Slots -----

void MainWindow::browseFiles()
{
	ui->fileBrowseLineEdit->setText(
		QFileDialog::getOpenFileName(
			this,
			tr("Select dfu binary"),
			QString(),
			tr("DFU Binary ( *.dfu.bin *.bin );;All Files ( * )")
		)
	);
}

// Make sure dfu-util can be found
bool MainWindow::checkDFU( QFile *dfuUtil )
{
	// Make sure dfu-util exists
	if ( !dfuUtil->exists() )
	{
		// Error, dfu-util not installed locally
		QString output = tr("dfu-util cannot be found. Either build dfu-util and copy the binary to this directory or symlink it.\ne.g. ln -s /usr/bin/dfu-util %1/.").arg( binaryPath );
		ui->dfuResultsTextEdit->append( output );

		return false;
	}

	return true;
}

void MainWindow::dfuFlashBinary()
{
	// Check if file exists
	QFile flashFile( ui->fileBrowseLineEdit->text() );
	if ( !flashFile.exists() )
	{
		// Error if no file selected
		if ( flashFile.fileName() == QString() )
		{
			QString output = tr("No file selected...");
			ui->dfuResultsTextEdit->append( output );
		}
		// Error if it doesn't exist
		else
		{
			QString output = tr("'%1' does not exist...").arg( flashFile.fileName() );
			ui->dfuResultsTextEdit->append( output );
		}

		return;
	}

	QFile dfuUtil( binaryPath + "/" + "dfu-util" );

	// Only run dfu-util if it exists
	if ( !checkDFU( &dfuUtil ) )
	{
		return;
	}

	// Run dfu-util command
	QString dfuCmd = QString("%1 -D %2").arg( dfuUtil.fileName(), flashFile.fileName() );
	dfuUtilProcess.start( dfuCmd );

	// Disable the flash button while command is running
	ui->flashButton->setDisabled( true );
	ui->listDevicesButton->setDisabled( true );
}

void MainWindow::dfuListDevices()
{
#ifdef WIN32
	QFile dfuUtil( binaryPath + "/" + "dfu-util.exe");
#else
	QFile dfuUtil( binaryPath + "/" + "dfu-util" );
#endif

	// Only run dfu-util if it exists
	if ( !checkDFU( &dfuUtil ) )
	{
		return;
	}

	// Run dfu-util command
	QString dfuCmd = QString("%1 -l").arg( dfuUtil.fileName() );
	dfuUtilProcess.start( dfuCmd );

	// Disable the flash button while command is running
	ui->flashButton->setDisabled( true );
	ui->listDevicesButton->setDisabled( true );
}

void MainWindow::dfuCommandStatus()
{
	// Append text to the viewer
	ui->dfuResultsTextEdit->append( dfuUtilProcess.readAllStandardOutput() );

	// Scroll to bottom
	ui->dfuResultsTextEdit->verticalScrollBar()->setValue( ui->dfuResultsTextEdit->verticalScrollBar()->maximum() );
}

void MainWindow::dfuCommandComplete( int exitCode )
{
	// Re-enable button after command completes
	ui->flashButton->setDisabled( false );
	ui->listDevicesButton->setDisabled( false );

	// Append return code
	QString output = tr("Return Code: %1").arg( exitCode );
	ui->dfuResultsTextEdit->append( output );
}

