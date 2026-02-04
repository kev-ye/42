import SwiftUI

struct SettingsView: View {
    @EnvironmentObject var appState: AppState
    @State private var showingColorPicker = false
    @State private var showingUserSwitch = false
    @State private var selectedColor: Color
    
    init() {
        _selectedColor = State(initialValue: .blue)
    }
    
    var body: some View {
        NavigationView {
            Form {
                Section(header: Text("user".localized)) {
                    if let user = appState.currentUser {
                        LabeledContent("phone_number".localized, value: user.phoneNumber)
                    }
                    
                    Button(action: { showingUserSwitch = true }) {
                        Text("switch_user".localized)
                    }
                    
                    Button(role: .destructive, action: logout) {
                        Text("logout".localized)
                    }
                }
                
                Section(header: Text("appearance".localized)) {
                    Button(action: { showingColorPicker = true }) {
                        HStack {
                            Text("header_color".localized)
                            Spacer()
                            Circle()
                                .fill(appState.headerColor)
                                .frame(width: 30, height: 30)
                        }
                    }
                }
            }
            .navigationTitle("settings".localized)
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .navigationBarLeading) {
                    Rectangle()
                        .fill(appState.headerColor)
                        .frame(width: 50, height: 4)
                }
            }
            .sheet(isPresented: $showingColorPicker) {
                ColorPickerView(selectedColor: $selectedColor) { color in
                    appState.saveHeaderColor(color)
                    showingColorPicker = false
                }
            }
            .sheet(isPresented: $showingUserSwitch) {
                UserSwitchView()
            }
            .onAppear {
                selectedColor = appState.headerColor
            }
        }
    }
    
    private func logout() {
        appState.logout()
    }
}

struct ColorPickerView: View {
    @Binding var selectedColor: Color
    let onSave: (Color) -> Void
    
    let colors: [Color] = [
        .blue, .red, .green, .orange, .purple,
        .pink, .yellow, .cyan, .indigo, .mint,
        .teal, .brown
    ]
    
    var body: some View {
        NavigationView {
            ScrollView {
                LazyVGrid(columns: [GridItem(.adaptive(minimum: 80))], spacing: 20) {
                    ForEach(colors, id: \.self) { color in
                        Circle()
                            .fill(color)
                            .frame(width: 60, height: 60)
                            .overlay(
                                Circle()
                                    .stroke(Color.primary, lineWidth: selectedColor == color ? 3 : 0)
                            )
                            .onTapGesture {
                                selectedColor = color
                            }
                    }
                }
                .padding()
            }
            .navigationTitle("select_color".localized)
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button("done".localized) {
                        onSave(selectedColor)
                    }
                }
            }
        }
    }
}

struct UserSwitchView: View {
    @EnvironmentObject var appState: AppState
    @Environment(\.dismiss) var dismiss
    @State private var users: [User] = []
    
    var body: some View {
        NavigationView {
            List {
                ForEach(users) { user in
                    Button(action: {
                        appState.setCurrentUser(phoneNumber: user.phoneNumber)
                        dismiss()
                    }) {
                        HStack {
                            VStack(alignment: .leading) {
                                Text(user.phoneNumber)
                                    .font(.headline)
                            }
                            Spacer()
                            if user.id == appState.currentUser?.id {
                                Image(systemName: "checkmark")
                                    .foregroundColor(.blue)
                            }
                        }
                    }
                }
            }
            .navigationTitle("switch_user".localized)
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button("cancel".localized) {
                        dismiss()
                    }
                }
            }
            .onAppear {
                users = DatabaseManager.shared.getAllUsers()
            }
        }
    }
}
