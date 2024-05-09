#include "server.h"

std::shared_ptr<Client> Server::add_client(std::string id) {
    for (auto& it : clients) {
        if (it.first->get_id() == id) {
            std::random_device rd;
            std::default_random_engine eng(rd());
            std::uniform_int_distribution<int> distr(1000, 9999);

            int n = distr(eng);
            std::stringstream t_id;
            t_id << n;
            std::string temp_id = t_id.str();
            id += temp_id;
            break;
        }
    }
    std::shared_ptr<Client> p = std::make_shared<Client>(id, *this);
    clients[p] = 5;
    return p;
}

std::shared_ptr<Client> Server::get_client(std::string id) const {
    for (auto& it : clients) {
        if (it.first->get_id() == id) {
            return it.first;
        }
    }
    return nullptr;
}

double Server::get_wallet(std::string id) const {
    for (auto& it : clients) {
        if (it.first->get_id() == id) {
            return it.second;
        }
    }
    return 0;
} 

void show_wallets(const Server& server) {
    std::cout << std::string(20, '*') << std::endl;
    for (const auto& client : server.clients) {
        std::cout << client.first->get_id() << " : " << client.second << std::endl;
    }
    std::cout << std::string(20, '*') << std::endl;
}

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) {
    int len = trx.size();
    int count = 0;
    std::string t_value;
    for (int i = 0; i < len; i++) {
        if (i == 0 && trx[i] == '-') {
            throw std::runtime_error("wrong trx");
        }
        if (trx[i] != '-' && count == 0) {
            sender += trx[i];
        }
        else if (trx[i] != '-' && count == 1) {
            receiver += trx[i];
        }
        else  if (trx[i] != '-' && count == 2) {
            t_value += trx[i];
        }
        else if (trx[i] == '-') {
            count++;
        }
    }   
    if (count != 2) {
        throw std::runtime_error("wrong trx");
    }
    std::stringstream temp(t_value);
    temp >> value;
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const {
    std::string sender, receiver;
    double value;
    parse_trx(trx, sender, receiver, value);
    if (sender == receiver) {
        return false;
    }
    std::shared_ptr<Client> sender_ptr = get_client(sender);
    std::shared_ptr<Client> receiver_ptr = get_client(receiver);
    if (receiver_ptr == nullptr) {
        return false;
    }
    if (clients.at(sender_ptr) < value) {
        return false;
    }
    std::string transaction_signature = sender_ptr->sign(trx);
    if (!crypto::verifySignature(sender_ptr->get_publickey(), trx, transaction_signature)) {
        return false;
    }
    pending_trxs.push_back(trx);
    return true;
}

size_t Server::mine() {
    std::string transaction;
    int len = pending_trxs.size();
    for (int i = 0; i < len; i++) {
        transaction += pending_trxs[i];
    }
    for (auto& it : clients) {
        std::string temp = transaction;
        size_t n = it.first->generate_nonce();
        std::stringstream t;
        t << n;
        std::string t_nonce;
        t >> t_nonce;
        temp += t_nonce;
        std::string ans = crypto::sha256(temp);
        if (ans.substr(0, 10).find("000") != std::string::npos) {
            clients[it.first] += 6.25;
            for (int i = 0; i < len; i++) {
                std::string sender, receiver;
                double value;
                parse_trx(pending_trxs[i], sender, receiver, value);
                std::shared_ptr<Client> sender_ptr = get_client(sender);
                std::shared_ptr<Client> receiver_ptr = get_client(receiver);
                clients[sender_ptr] -= value;
                clients[receiver_ptr] += value;
            }
            return n;
        }

    }
    return 0;
}