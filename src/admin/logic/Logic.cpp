/*
 *  Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License
 */
/*
 * @file        Logic.cpp
 * @author      Lukasz Wojciechowski <l.wojciechow@partner.samsung.com>
 * @version     1.0
 * @brief       This file contains implementation of Logic class - main libcynara-admin class
 */

#include <memory>

#include <common.h>
#include <protocol/Protocol.h>
#include <protocol/ProtocolAdmin.h>
#include <sockets/SocketClient.h>

#include "Logic.h"

namespace Cynara {

const std::string adminSocketPath("/run/cynara/cynara-admin.socket");

Logic::Logic() {
    m_socketClient = std::make_shared<SocketClient>(adminSocketPath,
                                                    std::make_shared<ProtocolAdmin>());
}

ProtocolFrameSequenceNumber generateSequenceNumber(void) {
    static ProtocolFrameSequenceNumber sequenceNumber = 0;
    return ++sequenceNumber;
}

int Logic::setPolicies(const std::map<PolicyBucketId, std::vector<Policy>> &insertOrUpdate UNUSED,
                const std::map<PolicyBucketId, std::vector<PolicyKey>> &remove UNUSED) noexcept {
//todo this is only a stub
    return CYNARA_ADMIN_API_SUCCESS;
}

int Logic::insertOrUpdateBucket(const PolicyBucketId &bucket UNUSED,
                                const PolicyResult &policyResult UNUSED) noexcept {
//todo this is only a stub
    return CYNARA_ADMIN_API_SUCCESS;
}

int Logic::removeBucket(const PolicyBucketId &bucket UNUSED) noexcept {
//todo this is only a stub
    return CYNARA_ADMIN_API_SUCCESS;
}

} // namespace Cynara
