class GameMenu extends PopupMenu
{
	TextListboxWidget m_gameScriptList;
	Widget 			  m_checkboxPanel;
	ButtonWidget 	  m_gameScriptButton;

	protected ref map< string, string > checkBoxMap = new map< string, string >; // store widget name

	string checkboxLayout = "$CurrentDir:missions\\DayZCommunityOfflineMode.Chiemsee\\core\\modules\\ComEditor\\gui\\layouts\\CheckboxTemplate.layout";

	void GameMenu()
	{
	}

	void ~GameMenu()
	{
	}

	override void Init()
	{
		m_checkboxPanel = layoutRoot.FindAnyWidget("game_checkbox_panel");
		m_gameScriptList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("game_list_box"));
		m_gameScriptButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("game_script_button"));

		m_gameScriptList.AddItem( "Spawn Hatchback", 		new Param1< string >( "SpawnHatchback" ), 	0 );
		m_gameScriptList.AddItem( "Spawn Sedan", 	 		new Param1< string >( "SpawnSedan" ), 	  	0 );
        m_gameScriptList.AddItem( "Spawn Gunter 2",  		new Param1< string >( "SpawnGunter" ),    	0 );
        m_gameScriptList.AddItem( "Spawn Sarka",     		new Param1< string >( "SpawnSarka" ),     	0 );
		m_gameScriptList.AddItem( "Spawn Truck Covered",	new Param1< string >( "SpawnCovered" ),		0 );

		CheckBoxWidget checkBoxGodmode = CheckBoxWidget.Cast(GetGame().GetWorkspace().CreateWidgets( checkboxLayout, m_checkboxPanel ));
		checkBoxGodmode.SetName( "Godmode" );
		checkBoxGodmode.SetText( "Godmode" );

//		CheckBoxWidget checkBoxAiming = CheckBoxWidget.Cast(GetGame().GetWorkspace().CreateWidgets( checkboxLayout, m_checkboxPanel ));
//		checkBoxAiming.SetName("OldAiming");
//		checkBoxAiming.SetText("Old Aiming");
//
//		CheckBoxWidget checkBoxLaser = CheckBoxWidget.Cast(GetGame().GetWorkspace().CreateWidgets( checkboxLayout, m_checkboxPanel ));
//		checkBoxLaser.SetName("LaserPointer");
//		checkBoxLaser.SetText("Laser Pointer");

		checkBoxMap.Insert( checkBoxGodmode.GetName(), "ToggleGodMode" );
//		checkBoxMap.Insert( checkBoxAiming.GetName(), "ToggleOldAiming" );
//		checkBoxMap.Insert( checkBoxLaser.GetName(), "ToggleLaser" );
	}

	override void OnShow()
	{
		// Update checkbox checked
		UpdateCheckBoxes();
	}

	override void OnHide() 
	{
		
	}

	void UpdateCheckBoxes() 
	{
		foreach( string widgetName, string function : checkBoxMap ) 
		{
			Widget widget = m_checkboxPanel.FindWidget( widgetName );

			if ( widget.IsInherited( CheckBoxWidget )) 
			{
				CheckBoxWidget checkbox = CheckBoxWidget.Cast( widget );
				bool checked;
				GetGame().GameScript.CallFunction( this , function , checked, NULL );
				checkbox.SetChecked( checked );
			}
		}
	}

	void Update() 
	{
	}

	bool ToggleOldAiming( CheckBoxWidget widget )
	{
		if ( widget ) // Temp work around. I'm lazy xd
		{
			m_COM_OldAiming = !m_COM_OldAiming;

			COM_GetPB().OverrideShootFromCamera( !m_COM_OldAiming );
		}
		return m_COM_OldAiming;
	}

	bool ToggleGodMode( CheckBoxWidget widget ) 
	{
		if ( widget ) 
		{
			m_COM_GodMode = !m_COM_GodMode;

			COM_GetPB().SetAllowDamage( !m_COM_GodMode );
		}
		return m_COM_GodMode;
	}

	bool ToggleLaser( CheckBoxWidget widget ) 
	{
		if ( widget ) 
		{
			COM_bc_Visible = !COM_bc_Visible;
		}
		return COM_bc_Visible;
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{

		string param;
		Param1<string> param1;

		if ( w == m_gameScriptButton ) 
		{
			int selectRow = m_gameScriptList.GetSelectedRow();

			if ( selectRow == -1 ) return false;

			m_gameScriptList.GetItemData( selectRow, 0, param1 );

			if ( param1 ) 
			{
				GetGame().GameScript.CallFunction( this , param1.param1 , NULL, 0 );
			}
		}

		if ( w.IsInherited( CheckBoxWidget ) ) 
		{
			param = checkBoxMap.Get( w.GetName() );

			if ( param ) 
			{
				GetGame().GameScript.CallFunction( this , param , NULL, CheckBoxWidget.Cast( w ) );
			}
		}

		return false;
	}

	void SpawnHatchback() 
	{
		TStringArray attArr = {
		"HeadlightH7","HeadlightH7",
		"HatchbackWheel","HatchbackWheel","HatchbackWheel","HatchbackWheel","HatchbackWheel",
		"CarBattery","CarRadiator","EngineBelt","SparkPlug","HatchbackHood",
		"HatchbackTrunk","HatchbackDoors_Driver","HatchbackDoors_CoDriver",
		};

		SpawnVehicle( "OffroadHatchback", attArr );
	}

	void SpawnSedan() 
	{
		TStringArray attArr = {
		"HeadlightH7","HeadlightH7",
		"CivSedanWheel","CivSedanWheel","CivSedanWheel","CivSedanWheel",
		"CarBattery","CarRadiator","EngineBelt","SparkPlug","CivSedanHood",
		"CivSedanTrunk","CivSedanDoors_Driver","CivSedanDoors_CoDriver",
		"CivSedanDoors_BackLeft","CivSedanDoors_BackRight",
		};

		SpawnVehicle( "CivilianSedan", attArr );
	}

	void SpawnGunter()
	{
		TStringArray attArr = {
		"HeadlightH7", "HeadlightH7","CarBattery","CarRadiator","SparkPlug","Hatchback_02_Door_1_1",
		"Hatchback_02_Door_1_2","Hatchback_02_Door_2_1","Hatchback_02_Door_2_2",
		"Hatchback_02_Trunk","Hatchback_02_Hood","Hatchback_02_Wheel","Hatchback_02_Wheel",
		"Hatchback_02_Wheel","Hatchback_02_Wheel","CivSedanDoors_BackRight",
		};

		SpawnVehicle( "Hatchback_02", attArr );
	}

	void SpawnSarka()
	{
		TStringArray attArr = {
		"HeadlightH7", "HeadlightH7","CarBattery","CarRadiator","SparkPlug","Sedan_02_Hood",
		"Sedan_02_Hood","Sedan_02_Trunk","Sedan_02_Door_1_1",
		"Sedan_02_Door_2_1","Sedan_02_Door_1_2","Sedan_02_Door_2_2","Sedan_02_Wheel",
		"Sedan_02_Wheel","Sedan_02_Wheel","Sedan_02_Wheel",
		};

		SpawnVehicle( "Sedan_02", attArr );
	}

	void SpawnCovered() 
	{
		TStringArray attArr = 
		{
			"Truck_01_Wheel","Truck_01_Wheel","Truck_01_Wheel","Truck_01_Wheel","Truck_01_WheelDouble","Truck_01_WheelDouble","Truck_01_WheelDouble","Truck_01_WheelDouble",
			"HeadlightH7","HeadlightH7","TruckBattery","Truck_01_Hood",
			"Truck_01_Door_1_1","Truck_01_Door_2_1"
		};

		SpawnVehicle( "Truck_01_Covered", attArr );
	}

	void SpawnVehicle( string vehicle, TStringArray attachments) 
	{
		Car oCar = Car.Cast( GetGame().CreateObject( vehicle, COM_GetCursorPos(), false, false ) );

		for (int j = 0; j < attachments.Count(); j++) { oCar.GetInventory().CreateAttachment( attachments.Get(j) ); }

		oCar.Fill( CarFluid.FUEL, 1000 );
		oCar.Fill( CarFluid.OIL, 1000 );
		oCar.Fill( CarFluid.BRAKE, 1000 );
		oCar.Fill( CarFluid.COOLANT, 1000 );

		//oCar.EngineStart();
		//oCar.SwitchLights();
	}
}