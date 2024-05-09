#include "client.h"
#include"server.h"

Client::Client(std::string id, const Server& server) : id(id), server(&server) {
    crypto::generate_key(public_key, private_key);
}

std::string Client::get_id() const {
    return id;
}

std::string Client::get_publickey() const {
    return public_key;
}

double Client::get_wallet() const {
    return server->get_wallet(id);
}

std::string Client::sign(std::string txt) const {
    return crypto::signMessage(private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value) {
    std::stringstream temp;
    temp << value;
    std::string t_value;
    temp >> t_value;
    std::string trx = this->id + "-" + receiver + "-" + t_value;
    std::string transaction_signature = sign(trx);
    if (server->add_pending_trx(trx, transaction_signature)) {
        return true;
    }
    return false;
}

size_t Client::generate_nonce() {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<size_t> distr(0, 9);
    return distr(eng);
}