// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// 	Author: W.J. Cheon
//  Major:
//  Radiolodical Science, Yonsei Univ., Korea. (B.S)
//  Communication and Information Eng., Computer Eng.,Yonsei Univ., Korea (B.Eng)
//  Medical Physics, Sungkyunkwan Univ., Korea (Ph.D integrated course)
//  Email: wonjoongcheon@gmail.com
//

#include "DetectorConstruction.hh"

#include "G4Box.hh"

#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"

#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4VisAttributes.hh"

#include "SensitiveDetector.hh"
#include "G4SystemOfUnits.hh"


//Share
#include "Shared.hh"


DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction()
{

}

DetectorConstruction::~DetectorConstruction()
{

}

void DetectorConstruction::SetDimension(){

	WorldX = 3.0*m;
	WorldY = 3.0*m;
	WorldZ = 3.0*m;

	WaterBoxX = 30*cm;
	WaterBoxY = 30*cm;
	WaterBoxZ = 1*cm;

	WaterBoxPositionX = 0.0*cm;
	WaterBoxPositionY = 0.0*cm;
	WaterBoxPositionZ = 0.0*cm;

	NumOfReplica = NUMBER_OF_REPLICA;


}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	SetDimension();


	// World
	G4VSolid* sol_World = new G4Box("World", WorldX*0.5,WorldY*0.5, WorldZ*0.5);
	G4Material* AIR = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
	G4LogicalVolume* lv_World = new G4LogicalVolume(sol_World, AIR, "World");
	G4VPhysicalVolume* pv_World =
			new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.0), lv_World, "World", 0, false, 0);

	// User geometry
	// Water box (x: 10 cm, y: 10 cm, z: 10 cm, at (0, 0, 0))
	G4VSolid* sol_Geom = new G4Box("Geom", WaterBoxX*0.5, WaterBoxY*0.5, WaterBoxZ*0.5);
	G4Material* WATER = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
	G4LogicalVolume* lv_Geom = new G4LogicalVolume(sol_Geom, WATER, "Geom");
	G4VPhysicalVolume* pv_Geom =
			new G4PVPlacement(0, G4ThreeVector(WaterBoxPositionX, WaterBoxPositionY, WaterBoxPositionZ), lv_Geom, "Geom", lv_World, false, 10);

	G4VSolid* sol_RepX = new G4Box("RepX",(WaterBoxX/NumOfReplica)*0.5,WaterBoxY*0.5,WaterBoxZ*0.5);
	G4LogicalVolume* lv_RepX = new G4LogicalVolume(sol_RepX,WATER,"RepX");
	G4VPhysicalVolume* pv_RepX = new G4PVReplica("RepX",lv_RepX,lv_Geom,kXAxis,NumOfReplica,WaterBoxX/NumOfReplica);

	G4VSolid* sol_RepY = new G4Box("RepY",(WaterBoxX/NumOfReplica)*0.5,(WaterBoxY/NumOfReplica)*0.5,WaterBoxZ*0.5);
	G4LogicalVolume* lv_RepY = new G4LogicalVolume(sol_RepY,WATER,"RepY");
	G4VPhysicalVolume* pv_RepY = new G4PVReplica("RepY",lv_RepY,lv_RepX,kYAxis,NumOfReplica,WaterBoxY/NumOfReplica);



	// Visualization
	G4VisAttributes* va_World = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
	va_World->SetForceWireframe(true);
	lv_World->SetVisAttributes(va_World);

	G4VisAttributes* va_Geom = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
	va_Geom->SetForceWireframe(true);
	lv_Geom->SetVisAttributes(va_Geom);

	G4VisAttributes* va_Rep = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0,0.3));
	va_Rep->SetForceWireframe(true);
	lv_RepX->SetVisAttributes(va_Rep);
	lv_RepY->SetVisAttributes(va_Rep);


	return pv_World;
}

void DetectorConstruction::ConstructSDandField()
{
	// Set sensitive detector on "Geom"
	SetSensitiveDetector("RepY", new SensitiveDetector("detector"));
}
