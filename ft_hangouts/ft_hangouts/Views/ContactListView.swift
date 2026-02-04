import SwiftUI

struct ContactListView: View {
    @EnvironmentObject var appState: AppState
    @State private var contacts: [Contact] = []
    @State private var showingAddContact = false
    
    var body: some View {
        NavigationView {
            List {
                ForEach(contacts) { contact in
                    NavigationLink(destination: ContactDetailView(contact: contact, onUpdate: loadContacts)) {
                        ContactRowView(contact: contact)
                    }
                }
                .onDelete(perform: deleteContacts)
            }
            .navigationTitle("contacts".localized)
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .navigationBarLeading) {
                    Rectangle()
                        .fill(appState.headerColor)
                        .frame(width: 50, height: 4)
                }
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button(action: { showingAddContact = true }) {
                        Image(systemName: "plus")
                    }
                }
            }
            .sheet(isPresented: $showingAddContact) {
                AddContactView(onSave: loadContacts)
            }
            .onAppear(perform: loadContacts)
        }
    }
    
    private func loadContacts() {
        if let userId = appState.currentUser?.id {
            // 先检查并自动创建从消息中来的联系人
            DatabaseManager.shared.checkAndCreateContactsFromMessages(forUserId: userId)
            // 然后加载联系人列表
            contacts = DatabaseManager.shared.getContacts(forUserId: userId)
        }
    }
    
    private func deleteContacts(at offsets: IndexSet) {
        for index in offsets {
            DatabaseManager.shared.deleteContact(contacts[index])
        }
        loadContacts()
    }
}

struct ContactRowView: View {
    let contact: Contact
    
    var body: some View {
        HStack {
            if let photoData = contact.photoData, let uiImage = UIImage(data: photoData) {
                Image(uiImage: uiImage)
                    .resizable()
                    .scaledToFill()
                    .frame(width: 50, height: 50)
                    .clipShape(Circle())
            } else {
                Image(systemName: "person.circle.fill")
                    .font(.system(size: 50))
                    .foregroundColor(.gray)
            }
            
            VStack(alignment: .leading, spacing: 4) {
                Text(contact.name)
                    .font(.headline)
                Text(contact.phoneNumber)
                    .font(.subheadline)
                    .foregroundColor(.gray)
            }
        }
        .padding(.vertical, 4)
    }
}
