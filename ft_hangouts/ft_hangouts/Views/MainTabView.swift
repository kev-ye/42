import SwiftUI

struct MainTabView: View {
    @EnvironmentObject var appState: AppState
    
    var body: some View {
        TabView {
            ContactListView()
                .tabItem {
                    Label("contacts".localized, systemImage: "person.2.fill")
                }
            
            MessagesListView()
                .tabItem {
                    Label("messages".localized, systemImage: "message.fill")
                }
            
            SettingsView()
                .tabItem {
                    Label("settings".localized, systemImage: "gear")
                }
        }
    }
}
