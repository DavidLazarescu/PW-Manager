#include "UI_Menu.h"

#include "UI_AddNote.h"
#include "UI_Settings.h"

#include "../Shared.h"



void showMenuWindow()
{
	Menu menu;
	
	int size{ 60 };

	// Components
	auto settingsButton = ftxui::Button("(settings)", showSettingsWindow);
	ftxui::ButtonOption newNoteButtonOption;
	newNoteButtonOption.border = true;
	auto newNoteButton = ftxui::Button("Add new note", showAddNoteWindow, newNoteButtonOption);
	auto generatePasswordButton = ftxui::Button(L"Generate", [&] { menu.generatePassword(); });
	auto copyPasswordButton = ftxui::Button("Copy To Clipboard", [&] { /*menu.copyPasswordToClipboard()*/; });


	ftxui::Component passwordLengthInput = ftxui::Input(&menu.generatedPasswordLength, L"0");


	auto lowercaseCheckBox = ftxui::Checkbox(L"include lowercase (e.g. abcd)", &menu.lowercaseLetters);
	auto uppercaseCheckBox = ftxui::Checkbox(L"include uppercase (e.g. ABCD)", &menu.uppercaseLetters);
	auto numbersCheckBox = ftxui::Checkbox(L"include numbers   (e.g. 1234)", &menu.includeNumbers);
	auto symbolsCheckBox = ftxui::Checkbox(L"include symbols   (e.g. @#$%)", &menu.includeSymbols);


	// Contains the currently owned notes of the user
	int selected = 0;
	std::vector<std::wstring> entries = menu.getUserNotes();

	ftxui::MenuOption vaultMenuOption;
	vaultMenuOption.on_enter = [] (){};
	auto vaultMenu = ftxui::Menu(&entries, &selected, vaultMenuOption);

	// Container
	auto container = ftxui::Container::Vertical({
			newNoteButton,
			vaultMenu,
			settingsButton,
			passwordLengthInput,
			lowercaseCheckBox,
			uppercaseCheckBox,
			numbersCheckBox,
			symbolsCheckBox,
			generatePasswordButton,
			copyPasswordButton
	});




	auto renderer = ftxui::Renderer(container, [&]
		{
			return
				ftxui::hbox(

					// Left side
					ftxui::vbox
					(
						ftxui::hbox
						(
							// Title
							ftxui::text(L"--- MY VAULT ---") | ftxui::center,
							newNoteButton->Render()
						),

						// Separator
						ftxui::separator(),

						// Notes menu
						vaultMenu->Render()

					) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 65),



					// Right side
					ftxui::vbox
					(
						ftxui::hbox
						(
							ftxui::text(std::wstring(pInfo::name.begin(), pInfo::name.end())) | ftxui::flex,
							settingsButton->Render() | ftxui::align_right,
							ftxui::text(L" ") | ftxui::align_right | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 10)
						),

						// Separator
						ftxui::separator(),

						// Spacing
						ftxui::text(L" "),

						// Password Generator
						ftxui::vbox
						(
							ftxui::text(L"Password Generator") | ftxui::color(ftxui::Color::White) | ftxui::hcenter,

							ftxui::separator(),

							ftxui::vbox
							(
								ftxui::hbox
								(
									ftxui::text(L"length: "),
									passwordLengthInput->Render() | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 4)
									| ftxui::bgcolor(ftxui::Color::Black) | ftxui::color(ftxui::Color::Green)
								),

								ftxui::separator() | ftxui::color(ftxui::Color::GrayDark),

								// Checkboxes
								lowercaseCheckBox->Render(),
								uppercaseCheckBox->Render(),
								numbersCheckBox->Render(),
								symbolsCheckBox->Render(),

								//Spacing
								ftxui::text(L" "),

								generatePasswordButton->Render() | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 8),



								ftxui::separator() | ftxui::color(ftxui::Color::GrayDark),


								ftxui::text(menu.generatedPassword) | ftxui::hcenter,


								ftxui::separator() | ftxui::color(ftxui::Color::GrayDark),

								copyPasswordButton->Render() | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 15)

							) | ftxui::color(ftxui::Color::White)

						) | ftxui::border




					) | ftxui::border | ftxui::flex
				);
	});

	screen.Loop(renderer);
}