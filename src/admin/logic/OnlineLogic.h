/*
 *  Copyright (c) 2014-2015 Samsung Electronics Co., Ltd All Rights Reserved
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
/**
 * @file        src/admin/logic/OnlineLogic.h
 * @author      Lukasz Wojciechowski <l.wojciechow@partner.samsung.com>
 * @version     1.0
 * @brief       This file contains definition of online version of Logic class
 */

#ifndef SRC_ADMIN_LOGIC_ONLINELOGIC_H_
#define SRC_ADMIN_LOGIC_ONLINELOGIC_H_

#include <sockets/SocketClient.h>

#include <api/ApiInterface.h>

namespace Cynara {

class OnlineLogic : public ApiInterface {
private:
    SocketClient m_socketClient;

    bool ensureConnection(void);
    template<typename Req, typename Res, typename... ReqArgs>
    int getResponse(std::shared_ptr<Res> &retResponse, ReqArgs&&... args);

public:
    OnlineLogic();
    virtual ~OnlineLogic() {};

    virtual int setPolicies(const ApiInterface::PoliciesByBucket &insertOrUpdate,
                            const ApiInterface::KeysByBucket &remove);
    virtual int insertOrUpdateBucket(const PolicyBucketId &bucket,
                                     const PolicyResult &policyResult);
    virtual int removeBucket(const PolicyBucketId &bucket);
    virtual int adminCheck(const PolicyBucketId &startBucket, bool recursive,
                           const PolicyKey &key, PolicyResult &result);
    virtual int listPolicies(const PolicyBucketId &bucket, const PolicyKey &filter,
                             std::vector<Policy> &policies);
    virtual int erasePolicies(const PolicyBucketId &startBucket, bool recursive,
                              const PolicyKey &filter);
    virtual int listDescriptions(std::vector<PolicyDescription> &descriptions);
};

} // namespace Cynara

#endif /* SRC_ADMIN_LOGIC_ONLINELOGIC_H_ */
